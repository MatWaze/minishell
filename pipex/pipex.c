/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/07/02 18:55:50 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "pwd/pwd.h"
#include "echo/echo.h"
#include "exit/exit.h"
#include "expansion/expansion.h"
#include "common/common.h"
#include "export/export.h"
#include "quotes/quotes.h"
#include "redirection/redirection.h"

extern int	g_exit_status;

char		*search_path(char *cmd, t_export **env);
char		**change_envp(t_export **env_list);
int			handle_unset(t_args *args, char **av);
int			handle_export(t_args *args, char **av);
int			handle_cd(t_args *args, char **av);
void		append_pid(int p, t_args *args);
void		fork_conditions(int pid, t_args *args, int error, int *ans);
void		restore_in_out(t_fd *p);

static void	run_external_command(t_args *args, t_fd *p, char **av, int *ans);
static int	handle_pipe(int j, t_args *args, t_fd *p, char **av);
static void	execute_command(char *first, char **av, t_args *args);
static int	run_command_if_builtin(char **av, t_args *args, int *code);

int	pipex(t_args *args)
{
	t_fd		p;
	int			ans;
	char		**av;

	ans = 0;
	p.tempin = dup(0);
	p.tempout = dup(1);
	p.fdin = dup(p.tempin);
	pipe(p.hdfd);
	args->j = 0;
	while (!ans && args->j < args->p_count + 1)
	{
		ans = (args->argv[args->j] == NULL) * 2;
		if (ans)
			print_error_msg("syntax error", "");
		av = remove_redirections(args->argv[args->j], &p,
				&args->export_list, g_exit_status);
		ans = !expand_list(av, &args->env_list, g_exit_status, 0) * 2;
		if (p.rfd != -1)
		{
			close(p.fdin);
			p.fdin = p.rfd;
		}
		dup2(p.fdin, 0);
		close(p.fdin);
		if (!ans && av[0])
			ans = handle_pipe(args->j, args, &p, av);
		args->j++;
		free_arr(av);
	}
	close(p.hdfd[0]);
	restore_in_out(&p);
	return (ans);
}

static int	handle_pipe(int j, t_args *args, t_fd *p, char **av)
{
	int		error;
	int		ans;
	int		pid;

	error = 0;
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
	int				ans;
	unsigned int	exit_status;

	ans = 1;
	exit_status = 0;
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
	{
		if (exit_too_many_arguments(av, code) == 0)
			*code = shell_exit(av[1], args, &exit_status);
	}
	else
		ans = 0;
	return (ans);
}

static void	execute_command(char *first, char **av, t_args *args)
{
	char		*cmd;
	char		**updated_envp;
	struct stat	f_info;

	cmd = search_path(first, &args->export_list);
	if (stat(first, &f_info) != -1 && (f_info.st_mode & S_IFMT) == S_IFDIR)
	{
		print_error_msg("is a directory", first);
		exit(126);
	}
	else if (!cmd || access(cmd, F_OK) != 0)
	{
		print_error_msg("command not found", first);
		exit(127);
	}
	else if (!((f_info.st_mode & S_IRUSR) || (f_info.st_mode & S_IXUSR) \
	|| (f_info.st_mode & S_IXUSR)) && access(cmd, X_OK) != 0)
	{
		print_error_msg("Permission denied", first);
		exit(126);
	}
	updated_envp = change_envp(&args->env_list);
	execve(cmd, av, updated_envp);
	print_error_msg(strerror(errno), first);
	exit(1);
}

static void	run_external_command(t_args *args, t_fd *p, char **av, int *ans)
{
	int		pid;
	char	tmp;

	*ans = 0;
	pid = fork();
	if (pid == 0)
	{

		close(p->fdin);
		close(p->fdout);
		close(p->hdfd[1]);
		if (args->hd_count && args->j == 0)
		{
			while (args->hd_count--)
				read(p->hdfd[0], &tmp, 1);
		}
		close(p->hdfd[0]);
		if ((ft_strchr(av[0], '/')) && access(av[0], F_OK) != 0)
		{
			print_error_msg("No such file or directory", av[0]);
			exit(127);
		}
		execute_command(av[0], av, args);
	}
	else if (pid == -1)
		*ans = 1;
	else if (pid > 0)
		append_pid(pid, args);
}
