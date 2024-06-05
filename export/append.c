/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:04:54 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/05 12:32:30 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "export/export.h"

static int	append_list(char *s, char *key, t_export *l1, t_export *l2)
{
	t_export	*new;
	t_keyval	*cont;
	int			count;
	int			count2;

	if (ft_strlen(l1->pair->key) > ft_strlen(key))
		count = ft_strlen(l1->pair->key);
	else
		count = ft_strlen(key);
	if (ft_strlen(l2->pair->key) > ft_strlen(key))
		count2 = ft_strlen(l2->pair->key);
	else
		count2 = ft_strlen(key);
	if (ft_strncmp(key, l1->pair->key, count) > 0 && \
		(ft_strncmp(l2->pair->key, key, count2) > 0 || l2 == NULL))
	{
		cont = ft_content_new(key, s);
		new = (t_export *) ft_lstnew(cont);
		new->next = l2;
		l1->next = new;
		return (1);
	}
	return (0);
}

static int	append_last(char *s, char *key, t_export *last)
{
	t_export	*new;
	t_keyval	*cont;
	int			count;
	int			ans;

	ans = 0;
	if (ft_strlen(key) > ft_strlen(last->pair->key))
		count = ft_strlen(key);
	else
		count = ft_strlen(last->pair->key);
	if (ft_strncmp(key, last->pair->key, count) > 0)
	{
		cont = ft_content_new(key, s);
		new = (t_export *) ft_lstnew(cont);
		last->next = new;
		new->next = NULL;
		ans = 1;
	}
	return (ans);
}

static void	append_to_empty(char *s, char *key, t_export **first)
{
	t_export	*new;
	t_keyval	*cont;

	cont = ft_content_new(key, s);
	new = (t_export *) ft_lstnew(cont);
	*first = new;
	new->next = NULL;
}

static int	append_first(char *s, char *key, t_export **first)
{
	t_export	*new;
	t_keyval	*cont;
	int			count;
	int			ans;

	ans = 0;
	if (*first == NULL)
		append_to_empty(s, key, first);
	else
	{
		if (ft_strlen(key) >= ft_strlen((*first)->pair->key))
			count = ft_strlen(key);
		else
			count = ft_strlen((*first)->pair->key);
		if (ft_strncmp((*first)->pair->key, key, count) > 0)
		{
			cont = ft_content_new(key, s);
			new = (t_export *) ft_lstnew(cont);
			new->next = *first;
			*first = new;
			ans = 1;
		}
	}
	return (ans);
}

void	append(char *s, char *key, t_export **l)
{
	t_export	*l1;
	t_export	*l2;

	if (append_first(s, key, l) == 0)
	{
		l2 = *l;
		l1 = *l;
		while (l1->next)
			l1 = l1->next;
		if (append_last(s, key, l1) == 0)
		{
			l1 = *l;
			l2 = l1->next;
			while (l1 && l2)
			{
				if (append_list(s, key, l1, l2) == 1)
					break ;
				l1 = l1->next;
				l2 = l1->next;
			}
		}
	}
}
