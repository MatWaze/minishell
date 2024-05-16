/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:13:06 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/16 13:12:44 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

char	**get_path(char **path)
{
	char	**strs1;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		strs1 = ft_split(path[i], '=');
		if (ft_strncmp(strs1[0], "PATH", 4) == 0)
			return (strs1);
		free_arr(strs1);
		i++;
	}
	return (NULL);
}

char	*search_path(char *cmd, char **path)
{
	char	**strs1;
	char	**strs2;

	strs1 = get_path(path);
	if (!strs1)
		return (NULL);
	strs2 = ft_split(strs1[1], ':');
	free_arr(strs1);
	return (get_str(strs2, cmd));
}

// wait(&status);
// exit_status = WEXITSTATUS(status);
// return (exit_status);
