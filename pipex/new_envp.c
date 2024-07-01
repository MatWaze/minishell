/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:36:50 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/06 11:53:18 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "export/export.h"

static void	populate_new_envp(char **envp, t_export *current);

char	**change_envp(t_export **env_list)
{
	t_export	*current;
	char		**envp;
	int			i;

	if (!env_list || !(*env_list))
		return (NULL);
	current = *env_list;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	envp = (char **) malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	current = *env_list;
	populate_new_envp(envp, current);
	return (envp);
}

void	populate_new_envp(char **envp, t_export *current)
{
	char	*key_value;
	char	*key_val;
	char	*joined;
	int		j;

	j = 0;
	while (current)
	{
		joined = ft_strdup(current->pair->key);
		key_value = ft_strjoin(joined, "=");
		free(joined);
		if (current->pair->val)
		{
			key_val = ft_strjoin(key_value, ft_strdup(current->pair->val));
			free(key_value);
		}
		else
			key_val = key_value;
		envp[j] = key_val;
		current = current->next;
		j++;
	}
	envp[j] = NULL;
}
