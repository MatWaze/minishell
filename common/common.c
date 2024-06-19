/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:11:41 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/19 16:25:02 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

void	print_error_msg(char *msg, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}

void	free_arr(char **av)
{
	int	i;

	i = 0;
	if (av)
	{
		while (av[i])
		{
			free(av[i]);
			i++;
		}
	}
	free(av);
}

int	ft_str_is_numeric(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
			{
				ans = 0;
				break ;
			}
			i++;
		}
	}
	return (ans);
}

int	ft_str_is_alpha(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	if (str)
	{
		while (str[i])
		{
			if (!(ft_isalpha(str[i]) || str[i] == '_'))
			{
				ans = 0;
				break ;
			}
			i++;
		}
	}
	return (ans);
}

int	ft_str_not_alpha(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	if (str)
	{
		while (str[i])
		{
			if (!(ft_isalnum(str[i]) || str[i] == '_'))
			{
				ans = 0;
				break ;
			}
			i++;
		}
	}
	return (ans);
}
