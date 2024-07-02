/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_runners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:45:20 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 21:58:27 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "pwd/pwd.h"
#include "echo/echo.h"
#include "exit/exit.h"
#include "common/common.h"
#include "export/export.h"
#include "t_args.h"

void	append_pid(int p, t_args *args);
void	close_fds(t_fd *p);
char	**change_envp(t_export **env_list);
char	*search_path(char *cmd, t_export **env);
int		handle_cd(t_args *args, char **av);
int		handle_unset(t_args *args, char **av);
int		handle_export(t_args *args, char **av);

int	run_command_if_builtin(char **av, t_args *args, int *code)
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
		if (exit_no_arguments(av[1], args) == 0)
			*code = shell_exit(av, &exit_status, args->p_count);
	}
	else
		ans = 0;
	return (ans);
}

void	execute_command(char *first, char **av, t_args *args)
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

void	run_external_command(t_args *args, char **av, int *ans)
{
	int		pid;
	char	tmp;

	*ans = 0;
	pid = fork();
	if (pid == 0)
	{
		close_fds(&args->p);
		if (args->hd_count && args->j == 0)
		{
			while (args->hd_count--)
				read(args->p.hdfd[0], &tmp, 1);
		}
		close(args->p.hdfd[0]);
		if ((ft_strchr(av[0], '/')) && access(av[0], F_OK) != 0)
		{
			print_error_msg("No such file or directory", av[0]);
			exit(127);
		}
		execute_command(av[0], av, args);
	}
	else if (pid == -1 && !close(args->p.fdin))
		*ans = 1;
	else if (pid > 0)
		append_pid(pid, args);
}
