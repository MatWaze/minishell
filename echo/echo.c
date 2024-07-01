/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:02:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/06 16:46:44 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

static void	set_flag(char **strs, int *i, int *flag);
static int	split_len(char **split);

int	echo(char **strs)
{
	int		flag;
	int		i;

	flag = 0;
	i = 1;
	if (split_len(strs) > 1)
	{
		set_flag(strs, &i, &flag);
		while (strs[i] != NULL)
		{
			ft_putstr_fd(strs[i], 1);
			if (strs[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

static int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

static void	set_flag(char **strs, int *i, int *flag)
{
	char	*trimmed;

	while (strs[*i] && strs[*i][0] == '-')
	{
		if (ft_strlen(strs[*i]) == 1 && strs[*i][0] == '-')
			break ;
		trimmed = ft_strtrim(strs[*i], "n");
		if (!(ft_strlen(trimmed) == 1 && ft_strncmp(trimmed, "-", 1) == 0))
		{
			free(trimmed);
			break ;
		}
		else
		{
			*flag = 1;
			free(trimmed);
		}
		(*i)++;
	}
}
