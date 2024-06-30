/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/29 20:54:20 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

#include "pwd/pwd.h"
#include "echo/echo.h"
#include "exit/exit.h"
#include "expansion/expansion.h"
#include "common/common.h"
#include "export/export.h"
#include "quotes/quotes.h"
#include "redirection/redirection.h"

char		*search_path(char *cmd, t_export **env);
char		**change_envp(t_export **env_list);
int			handle_unset(t_args *args, char **av);
int			handle_export(t_args *args, char **av);
int			handle_cd(t_args *args, char **av);
void		append_pid(int p, t_args *args);
void		fork_conditions(pid_t pid, t_args *args, int error, int *ans);
void		restore_in_out(t_fd *p);

static void	run_external_command(t_args *args, t_fd *p, char **av, int *ans);
static int	handle_pipe(int j, t_args *args, t_fd *p, char **av);
static void	execute_command(char *first, char **av, t_args *args);
static int	run_command_if_builtin(char **av, t_args *args, int *code);

int	pipex(t_args *args)
{
	t_fd		p;
	int			j;
	int			ans;
	char		**av;

	ans = 0;
	p.tempin = dup(0);
	p.tempout = dup(1);
	// Prime pipe
	//pipe(p.fd);
	//dup2(p.fd[1], 0);
	//close(p.fd[1]);
	p.fdin = 0;
	j = 0;
	while (!ans && j < args->p_count + 1)
	{
		p.rfd = -1;
		p.wfd = -1;
		av = remove_redirections(args->argv[j], &p, &args->export_list,
				args->exit_code);
		ans = !expand_list(av, &args->env_list, args->exit_code) * 2;
		if (ans)
			args->exit_code = 1;
		if (p.rfd != -1)
			p.fdin = p.rfd;
		dup2(p.fdin, 0);
		if (p.fdin)
			close(p.fdin);
		if (!ans && av[0])
			ans = handle_pipe(j, args, &p, av);
		j++;
		free_arr(av);
	}
	restore_in_out(&p);
	return (ans);
}

static int	handle_pipe(int j, t_args *args, t_fd *p, char **av)
{
	pid_t	pid;
	int		error;
	int		ans;

	ans = 0;
	if (j == args->p_count && p->wfd == -1)
		p->fdout = dup(p->tempout);
	else if (j == args->p_count)
		p->fdout = p->wfd;
	else
	{
		pipe(p->fd);
		if (p->wfd == -1)
			p->fdout = p->fd[1];
		else
		{
			close(p->fd[1]);
			p->fdout = p->wfd;
		}
		p->fdin = p->fd[0];
	}
	dup2(p->fdout, 1);
	close(p->fdout);
	if (run_command_if_builtin(av, args, &error))
	{
		pid = fork();
		fork_conditions(pid, args, error, &ans);
	}
	else
		run_external_command(args, p, av, &ans);
	return (ans);
}

static int	run_command_if_builtin(char **av, t_args *args, int *code)
{
	int		ans;

	*code = 0;
	ans = 1;
	if (ft_strlen(av[0]) == 6 && ft_strncmp("export", av[0], 6) == 0)
		*code = handle_export(args, av);
	else if (ft_strlen(av[0]) == 3 && ft_strncmp("env", av[0], 3) == 0)
		print_list(&args->env_list, 0);
	else if (ft_strlen(av[0]) == 5 && ft_strncmp("unset", av[0], 5) == 0)
		*code = handle_unset(args, av);
	else if (ft_strlen(av[0]) == 4 && ft_strncmp("echo", av[0], 4) == 0)
		*code = echo(&av[0]);
	else if (ft_strlen(av[0]) == 3 && ft_strncmp("pwd", av[0], 3) == 0)
		free(pwd(1));
	else if (ft_strlen(av[0]) == 2 && ft_strncmp("cd", av[0], 2) == 0)
		*code = handle_cd(args, av);
	else if (ft_strlen(av[0]) == 4 && ft_strncmp("exit", av[0], 4) == 0)
		shell_exit(av[1], args);
	else
		ans = 0;
	return (ans);
}

static void	execute_command(char *first, char **av, t_args *args)
{
	char		*command;
	char		**updated_envp;
	struct stat	file_info;

	if (stat(first, &file_info) != -1
		&& (file_info.st_mode & S_IFMT) == S_IFDIR)
	{
		print_error_msg("is a directory\n", first);
		exit(126);
	}
	command = search_path(first, &args->export_list);
	if (command == NULL || access(command, F_OK) != 0)
	{
		print_error_msg("command not found\n", first);
		exit(127);
	}
	if (access(command, X_OK) != 0)
	{
		print_error_msg("Permission denied\n", first);
		exit(126);
	}
	updated_envp = change_envp(&args->env_list);
	if (execve(command, av, updated_envp) == -1)
		perror(first);
	exit(1);
}

static void	run_external_command(t_args *args, t_fd *p, char **av, int *ans)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		close(p->fdin);
		close(p->fdout);
		if (av[0][0] == '/' && access(av[0], F_OK) != 0)
		{
			print_error_msg("No such file or directory\n", av[0]);
			exit(127);
		}
		execute_command(av[0], av, args);
	}
	else if (pid == -1)
		*ans = 1;
	else if (pid > 0)
		append_pid(pid, args);
}
