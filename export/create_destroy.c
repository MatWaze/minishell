/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:08:18 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/04 19:16:05 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"
#include "t_export.h"

void	populate(t_export **l, char *key)
{
	char		*val;
	t_export	*new;
	t_keyval	*cont;
	t_export	*last;

	val = getenv(key);
	cont = ft_content_new(key, val);
	new = (t_export *) ft_lstnew(cont);
	if (*l == NULL)
		*l = new;
	else
	{
		last = *l;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	new->next = NULL;
}

t_keyval	*ft_content_new(char *key, char *val)
{
	t_keyval	*result;

	result = (t_keyval *) malloc(sizeof(t_keyval));
	if (result)
	{
		result->key = ft_strdup(key);
		result->val = ft_strdup(val);
		result->next = NULL;
	}
	return (result);
}

void	free_export_content(t_keyval *content)
{
	free(content->key);
	free(content->val);
	free(content);
}
