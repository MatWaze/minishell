/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:13:06 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/17 15:56:28 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

char	*get_path(t_export **env)
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

char	*search_path(char *cmd, t_export **env)
{
	char	*strs1;
	char	**strs2;

	strs1 = get_path(env);
	if (!strs1)
		return (NULL);
	strs2 = ft_split(strs1, ':');
	return (get_str(strs2, cmd));
}

// wait(&status);
// exit_status = WEXITSTATUS(status);
// return (exit_status);
