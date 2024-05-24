/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/24 18:39:42 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

void	free_arr(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	free_all(char **av, char *cmd)
{
	free_arr(av);
	free(cmd);
}

char	*get_str(char **strs2, char *cmd)
{
	char	*str;
	int		i;
	char	*s;

	i = 0;
	// if (!cmd)
	// 	return (NULL);
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

void	leave_children(void)
{
	int	i;
	int	status;

	i = wait(&status);
	while (i != -1)
		i = wait(&status);
}

void	close_all(int fd[], int argc)
{
	int	i;

	i = 0;
	while (i < argc * 2)
	{
		close(fd[i]);
		i++;
	}
}
