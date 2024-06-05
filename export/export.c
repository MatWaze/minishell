/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:42:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/05 12:19:08 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "common/common.h"
#include "libft/libft.h"
#include "t_args.h"

void		append(char *s, char *key, t_export **l);

static int	is_inside(char *s, char *key, t_export **l);
static void	append_to_lists(char *val, char *val2, char *key, t_args *args);
static void	free_values(char *val, char *val2, char **split);
static char	*get_val(char *s);

int	export(t_args *args, char *s)
{
	char	**split;
	char	*key;
	char	*val;
	char	*val2;
	int		ans;

	split = ft_split(s, '=');
	key = split[0];
	val = get_val(s);
	val2 = get_val(s);
	if (ft_isalpha(*key) == 1 || *key == '_')
	{
		if (args->p_count == 0 && (ft_strlen(key) >= 1 && \
			is_inside(val2, key, &args->env_list) == 0) || \
			is_inside(val, key, &args->export_list) == 0)
			append_to_lists(val, val2, key, args);
		ans = 0;
	}
	else
	{
		print_error_msg("not a valid identifier\n", key);
		ans = 1;
	}
	free_values(val, val2, split);
	return (ans);
}

static char	*get_val(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (ft_strchr(s, '=') == NULL)
		str = NULL;
	else
	{
		while (s[i] != '=')
			i++;
		if (s[i] == '=')
			i++;
		if (s[i] == '\0')
			str = ft_strdup("");
		else
			str = ft_strdup(&s[i]);
	}
	return (str);
}

static int	is_inside(char *s, char *key, t_export **l)
{
	int			ans;
	int			count;
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
			free(temp->pair->val);
			temp->pair->val = ft_strdup(s);
			ans = 1;
		}
		temp = temp->next;
	}
	return (ans);
}

static void	append_to_lists(char *val, char *val2, char *key, t_args *args)
{
	append(val, key, &args->export_list);
	append(val2, key, &args->env_list);
}

static void	free_values(char *val, char *val2, char **split)
{
	free_arr(split);
	free(val);
	free(val2);
}
