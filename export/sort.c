/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:55:21 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/03 18:02:34 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"
#include "t_export.h"

static void	ft_swap(t_export **l1, t_export **l2);

static void	ft_swap(t_export **l1, t_export **l2)
{
	char	*temp;
	char	*temp2;

	temp = (*l2)->pair->key;
	temp2 = (*l2)->pair->val;
	(*l2)->pair->key = (*l1)->pair->key;
	(*l2)->pair->val = (*l1)->pair->val;
	(*l1)->pair->key = temp;
	(*l1)->pair->val = temp2;
}

void	sort_list(t_export **l)
{
	t_export	*l1;
	t_export	*l2;
	int			count;

	l1 = *l;
	while (l1)
	{
		l2 = l1->next;
		while (l2)
		{
			if (ft_strlen(l1->pair->key) > ft_strlen(l2->pair->key))
				count = ft_strlen(l1->pair->key);
			else
				count = ft_strlen(l2->pair->key);
			if (ft_strncmp(l1->pair->key, l2->pair->key, count) > 0)
				ft_swap(&l1, &l2);
			l2 = l2->next;
		}
		l1 = l1->next;
	}
}
