/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:01:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/04 19:02:52 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
