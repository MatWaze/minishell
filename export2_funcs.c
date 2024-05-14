/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:04:54 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/14 16:05:41 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

int	append_list(char *s, char **split, t_export *l1, t_export *l2)
{
	t_export	*new;
	t_content	*cont;
	char		*val;
	int			count;
	int			count2;
	
	if (ft_strlen(l1->pair->key) > ft_strlen(split[0]))
		count = ft_strlen(l1->pair->key);
	else
		count = ft_strlen(split[0]);
	if (ft_strlen(l2->pair->key) > ft_strlen(split[0]))
		count2 = ft_strlen(l2->pair->key);
	else
		count2 = ft_strlen(split[0]);
	if (ft_strncmp(split[0], l1->pair->key, count) > 0 && \
		(ft_strncmp(l2->pair->key, split[0], count2) > 0 || l2 == NULL))
	{
		val = get_val(s);
		cont = ft_content_new(split[0], val);
		new = (t_export *) ft_lstnew(cont);
		new->next = l2;
		l1->next = new;
		return (1);
	}
	return (0);
}

int	append_last(char *s, char **split, t_export *last)
{
	t_export	*new;
	t_content	*cont;
	int			count;
	int			ans;
		
	ans = 0;
	if (ft_strlen(split[0]) > ft_strlen(last->pair->key))
		count = ft_strlen(split[0]);
	else
		count = ft_strlen(last->pair->key);
	if (ft_strncmp(split[0], last->pair->key, count) > 0)
	{
		cont = ft_content_new(split[0], get_val(s));
		new = (t_export *) ft_lstnew(cont);
		last->next = new;
		new->next = NULL;
		ans = 1;
	}
	return (ans);
}

int	append_first(char *s, char **split, t_export **first)
{
	t_export	*new;
	t_content	*cont;
	int			count;
	int			ans;
		
	ans = 0;
	if (ft_strlen(split[0]) >= ft_strlen((*first)->pair->key))
		count = ft_strlen(split[0]);
	else
		count = ft_strlen((*first)->pair->key);
	if (ft_strncmp((*first)->pair->key, split[0], count) > 0)
	{
		cont = ft_content_new(split[0], get_val(s));
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
	char		*str;
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
			str = get_val(s);
			if (str)
				temp->pair->val = str;
			ans = 1;
		}
		temp = temp->next;
	}
	return (ans);
}

void	append(char *s, char **split, t_export **l)
{
	t_export	*new;
	t_export	*l1;
	t_export	*l2;

	if  (append_first(s, split, l) == 0)
	{
		l2 = *l;
		l1 = *l;
		while (l1->next)
			l1 = l1->next;
		if (append_last(s, split, l1) == 0)
		{
			l1 = *l;
			l2 = l1->next;
			while (l1 && l2)
			{
				if (append_list(s, split, l1, l2) == 1)
					break ;
				l1 = l1->next;
				l2 = l1->next;
			}
		}
	}	
}