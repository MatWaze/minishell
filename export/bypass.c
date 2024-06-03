/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bypass.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:55:10 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/03 18:01:55 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "t_export.h"
#include "libft/libft.h"

int	find_key(t_export *export_list, char *key)
{
	t_export	*temp;
	int			ans;

	ans = 0;
	temp = export_list;
	while (temp)
	{
		if (key && ft_strncmp(temp->pair->key, key, ft_strlen(key)) == 0)
		{
			ans = 1;
			break ;
		}
		temp = temp->next;
	}
	return (ans);
}

void	print_list(t_export **list, int i)
{
	t_export	*temp;
	char		*val;

	temp = *list;
	while (temp != NULL)
	{
		val = temp->pair->val;
		if (i == 1)
		{
			if (val == NULL)
				printf("declare -x %s\n", temp->pair->key);
			else if (ft_strlen(val) == 0)
				printf("declare -x %s=\"\"\n", temp->pair->key);
			else
				printf("declare -x %s=\"%s\"\n", temp->pair->key, \
					temp->pair->val);
		}
		else
		{
			if (val != NULL)
				printf("%s=%s\n", temp->pair->key, \
					temp->pair->val);
		}
		temp = temp->next;
	}
}

char	*get_value_from_key(t_export **list, char *key)
{
	t_export	*temp;
	char		*ans;

	temp = *list;
	ans = NULL;
	while (temp)
	{
		if (ft_strncmp(key, temp->pair->key, \
			ft_strlen(temp->pair->key)) == 0)
		{
			ans = temp->pair->val;
			break ;
		}
		temp = temp->next;
	}
	return (ans);
}
