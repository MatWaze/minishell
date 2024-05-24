/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:04:54 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/24 13:21:14 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

int	append_list(char *s, char *key, t_export *l1, t_export *l2)
{
	t_export	*new;
	t_content	*cont;
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

int	append_last(char *s, char *key, t_export *last)
{
	t_export	*new;
	t_content	*cont;
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

int	append_first(char *s, char *key, t_export **first)
{
	t_export	*new;
	t_content	*cont;
	int			count;
	int			ans;

	ans = 0;
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
	return (ans);
}

int	is_inside(char *s, char *key, t_export **l)
{
	int			ans;
	int			count;
	//char		*str;
	t_export	*temp;

	ans = 0;
	temp = *l;
	while (temp)
	{
		if (ft_strlen(temp->pair->key) >= ft_strlen(key))
			count = ft_strlen(temp->pair->key);
		else
			count = ft_strlen(key);
		if (ft_strncmp(key, temp->pair->key, count) == 0)
		{
			// if (str)
			temp->pair->val = s;
			ans = 1;
		}
		temp = temp->next;
	}
	return (ans);
}

void	append(char *s, char *key, t_export **l)
{
	//t_export	*new;
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
