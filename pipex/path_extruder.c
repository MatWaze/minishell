/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_extruder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/05 13:03:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "export/t_export.h"
#include "libft/libft.h"
#include "common/common.h"

static char	*get_path(t_export **env);
static char	*get_str(char **strs2, char *cmd);

char	*search_path(char *cmd, t_export **env)
{
	char	*strs1;
	char	**strs2;

	strs1 = get_path(env);
	if (!strs1)
		return (cmd);
	strs2 = ft_split(strs1, ':');
	return (get_str(strs2, cmd));
}

static char	*get_str(char **strs2, char *cmd)
{
	char	*str;
	int		i;
	char	*s;

	i = 0;
	s = ft_strjoin("/", cmd);
	while (strs2[i] != NULL)
	{
		str = ft_strjoin(strs2[i++], s);
		if (access(str, F_OK) == 0)
		{
			free_arr(strs2);
			free(s);
			return (str);
		}
		free(str);
	}
	free_arr(strs2);
	free(s);
	return (cmd);
}

static char	*get_path(t_export **env)
{
	t_export	*temp;
	char		*key;
	char		*val;
	int			count;

	temp = *env;
	val = NULL;
	while (temp)
	{
		key = temp->pair->key;
		count = ft_strlen(key);
		if (ft_strncmp("PATH", key, count) == 0)
		{
			if (temp->pair->val)
				val = temp->pair->val;
			break ;
		}
		temp = temp->next;
	}
	return (val);
}
