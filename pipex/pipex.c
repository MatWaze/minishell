/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/03 19:57:55 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>

#include "export/export.h"
#include "t_args.h"
#include "t_fd.h"

void	append_pid(int p, t_args *args);

void	handle_builtin(char **av, t_args *args)
{
	char	*pwd;
	int		ans;

	ans = 0;
	if (ft_strlen(av[0]) == 6 && ft_strncmp("export", av[0], 6) == 0)
		ans = handle_export(args, av);
	else if (ft_strlen(av[0]) == 3 && ft_strncmp("env", av[0], 3) == 0)
		print_list(&args->env_list, 0);
	else if (ft_strlen(av[0]) == 5 && ft_strncmp("unset", av[0], 5) == 0)
		ans = handle_unset(args, av);
	else if (ft_strlen(av[0]) == 4 && ft_strncmp("echo", av[0], 4) == 0)
		ans = echo(&av[0]);
	else if (ft_strlen(av[0]) == 3 && ft_strncmp("pwd", av[0], 3) == 0)
	{
		pwd = my_pwd(1);
		free(pwd);
	}
	else if (ft_strlen(av[0]) == 2 && ft_strncmp("cd", av[0], 2) == 0)
		ans = handle_cd(args, av);
	else if (ft_strlen(av[0]) == 4 && ft_strncmp("exit", av[0], 4) == 0)
		shell_exit(av[1]);
	builtin_exit_code(ans, args);
}

int	is_dir(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1)
		return (0);
	return (((file_info.st_mode) & S_IFMT) == S_IFDIR);
}

void	dir_error(char *first)
{
	if (is_dir(first) != 0)
	{
		print_error_msg("is a directory\n", first);
		exit(126);
	}
}

void	execute_command(char *first, char **av, char **envp, t_args *args)
{
	char	*command;

	dir_error(first);
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
	if (execve(command, av, envp) == -1)
		print_error_msg("error", first);
	exit(1);
}

void	append_pid(int p, t_args *args)
{
	int		*pid_copy;
	t_list	*new;
	t_list	*last;

	pid_copy = (int *)malloc(sizeof(int));
	*pid_copy = p;
	new = ft_lstnew(pid_copy);
	if (!args->pids)
		args->pids = new;
	else
	{
		last = args->pids;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	new->next = NULL;
}

void	handle_command(char **av, t_args *args)
{
	if (av[0][0] == '/' && access(av[0], F_OK) != 0)
	{
		print_error_msg("No such file or directory\n", av[0]);
		exit(127);
	}
	execute_command(av[0], av, args->envp, args);
}

void	run_command(t_args *args, t_fd *p, char **av)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		close(p->fdin);
		close(p->fdout);
		handle_command(av, args);
	}
	else if (pid == -1)
		print_error_msg("failed\n", "fork");
	else if (pid > 0)
		append_pid(pid, args);
}

void	handle_pipe(int j, t_args *args, t_fd *p)
{
	char	**av;

	dup2(p->fdin, 0);
	close(p->fdin);
	av = quoted_split(args->argv[j], ' ');
	if (expand_list(av, &args->env_list, args->exit_code))
	{
		if (j == args->p_count)
			p->fdout = dup(p->tempout);
		else
		{
			pipe(p->fd);
			p->fdout = p->fd[1];
			p->fdin = p->fd[0];
		}
		dup2(p->fdout, 1);
		close(p->fdout);
		if (is_builtin(av[0]) == 1)
			handle_builtin(av, args);
		else
			run_command(args, p, av);
	}
	free_arr(av);
}

void	pipex(t_args *args)
{
	t_fd	p;
	int		j;

	p.tempin = dup(0);
	p.tempout = dup(1);
	p.fdin = dup(p.tempin);
	j = 0;
	while (j < args->p_count + 1)
		handle_pipe(j++, args, &p);
	dup2(p.tempin, 0);
	dup2(p.tempout, 1);
	close(p.tempin);
	close(p.tempout);
}
