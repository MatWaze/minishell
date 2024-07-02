/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:01:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 18:56:32 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

#include "t_args.h"

extern int	g_exit_status;

void	append_pid(int p, t_args *args)
{
	int		*pid_copy;
	t_list	*new;
	t_list	*last;

	pid_copy = (int *)malloc(sizeof(int));
	if (pid_copy)
	{
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
}

void	fork_conditions(int pid, t_args *args, int error, int *ans)
{
	if (pid == 0)
		exit(error);
	else if (pid == -1)
	{
		close(args->fds.fdin);
		*ans = 1;
	}
	else
		append_pid(pid, args);
}

void	kill_processes(t_list *pids)
{
	t_list	*temp;

	temp = pids;
	while (temp)
	{
		kill(*(int *) temp->content, SIGKILL);
		waitpid(*(int *) temp->content, NULL, 0);
		temp = temp->next;
	}
}

void	get_exit_status(t_list *pids)
{
	t_list	*list;
	int		exit_status;
	pid_t	pid;

	list = pids;
	while (list)
	{
		pid = waitpid(*(int *) list->content, &exit_status, 0);
		while (pid == -1 && errno == EINTR)
			pid = waitpid(*(int *) list->content, &exit_status, 0);
		list = list->next;
	}
	if (WIFEXITED(exit_status))
		g_exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		g_exit_status = 128 + WTERMSIG(exit_status);
}
