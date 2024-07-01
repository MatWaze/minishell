/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:01:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/18 16:18:17 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>

#include "t_args.h"

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

void	fork_conditions(pid_t pid, t_args *args, int error, int *ans)
{
	if (pid == 0)
		exit(error);
	else if (pid == -1)
		*ans = 1;
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
		temp = temp->next;
	}
}

void	get_exit_status(t_args *args)
{
	t_list	*list;

	list = args->pids;
	while (list)
	{
		waitpid(*(int *) list->content, &args->exit_code, 0);
		list = list->next;
	}
	args->exit_code = WEXITSTATUS(args->exit_code);
}
