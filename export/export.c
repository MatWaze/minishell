/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:55:10 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/01 10:58:19 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

#include "t_export.h"
#include "libft/libft.h"

char	*find_val(t_export *l, char *to_find)
{
	t_export	*temp;
	char		*ans;
	int			count;

	ans = NULL;
	temp = l;
	while (temp)
	{
		if (ft_strlen(temp->pair->key) > ft_strlen(to_find))
			count = ft_strlen(temp->pair->key);
		else
			count = ft_strlen(to_find);
		if (ft_strncmp(temp->pair->key, to_find, count) == 0)
		{
			ans = temp->pair->val;
			break ;
		}
		temp = temp->next;
	}
	return (ans);
}
