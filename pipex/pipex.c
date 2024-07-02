/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/07/02 21:58:24 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "expansion/expansion.h"
#include "common/common.h"
#include "export/export.h"
#include "quotes/quotes.h"
#include "redirection/redirection.h"

extern int	g_exit_status;

void		fork_conditions(int pid, t_args *args, int error, int *ans);
void		restore_fd(t_fd *p);
int			run_command_if_builtin(char **av, t_args *args, int *code);
void		run_external_command(t_args *args, char **av, int *ans);

static int	handle_pipe(int j, t_args *args, char **av);
static void	initialize_pipex(t_args *args);
static void	redirect_handle_pipe(t_args *args);

int	pipex(t_args *args, int ans)
{
	char		**av;

	initialize_pipex(args);
	while (!ans && args->j < args->p_count + 1)
	{
		ans = (args->argv[args->j] == NULL) * 2;
		if (ans)
			print_error_msg("syntax error", "");
		av = remove_redirections(args->argv[args->j], &args->p,
				&args->export_list, g_exit_status);
		ans = !expand_list(av, &args->env_list, g_exit_status, 0) * 2;
		if (args->p.rfd != -1)
		{
			close(args->p.fdin);
			args->p.fdin = args->p.rfd;
		}
		dup2(args->p.fdin, 0);
		close(args->p.fdin);
		if (!ans && av[0])
			ans = handle_pipe(args->j, args, av);
		args->j++;
		free_arr(av);
	}
	restore_fd(&args->p);
	return (ans);
}

static void	initialize_pipex(t_args *args)
{
	args->p.tempin = dup(0);
	args->p.tempout = dup(1);
	args->p.fdin = dup(args->p.tempin);
	pipe(args->p.hdfd);
	args->j = 0;
}

static int	handle_pipe(int j, t_args *args, char **av)
{
	int		error;
	int		ans;
	int		pid;

	error = 0;
	ans = 0;
	if (j == args->p_count && args->p.wfd == -1)
		args->p.fdout = dup(args->p.tempout);
	else if (j == args->p_count)
		args->p.fdout = args->p.wfd;
	else
		redirect_handle_pipe(args);
	dup2(args->p.fdout, 1);
	close(args->p.fdout);
	if (run_command_if_builtin(av, args, &error))
	{
		pid = fork();
		fork_conditions(pid, args, error, &ans);
	}
	else
		run_external_command(args, av, &ans);
	return (ans);
}

static void	redirect_handle_pipe(t_args *args)
{
	pipe(args->p.fd);
	if (args->p.wfd == -1)
		args->p.fdout = args->p.fd[1];
	else
	{
		close(args->p.fd[1]);
		args->p.fdout = args->p.wfd;
	}
	args->p.fdin = args->p.fd[0];
}
