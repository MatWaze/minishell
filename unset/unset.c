/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:23:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/03 19:54:48 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "export/export.h"
#include "libft/libft.h"

void	my_unset(t_export **l, char *str)
{
	t_export	*temp;
	t_export	*prev;
	int			count;

	prev = NULL;
	temp = *l;
	while (temp)
	{
		if (ft_strlen(str) == ft_strlen(temp->pair->key))
		{
			count = ft_strlen(temp->pair->key);
			if (ft_strncmp(str, temp->pair->key, count) == 0)
			{
				if (prev == NULL)
					*l = temp->next;
				else
					prev->next = temp->next;
				free_export_content(temp->pair);
				free(temp);
				break ;
			}
		}
		prev = temp;
		temp = temp->next;
	}
}
