/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:10:19 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 19:07:30 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "common/common.h"
#include "t_args.h"

static void	negative_number_exit(unsigned int *exit_status, \
	char *num_str, char *neg_num_str);
static void	positive_number_exit(unsigned int *exit_status, char *num_str);
static void	not_valid_arg(unsigned int *temp_exit_status, char *num_str);

int	exit_no_arguments(char *num_str, t_args *args)
{
	int	ans;

	ans = 0;
	if (!num_str && args->p_count == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (!num_str)
		ans = 1;
	return (ans);
}

static void	negative_number_exit(unsigned int *exit_status, char *num_str, \
	char *neg_num_str)
{
	unsigned long long	pos_num;
	unsigned long long	to_compare;
	unsigned long long	neg_num;
	char				*joined;

	to_compare = (unsigned long long) 9223372036854775808U;
	neg_num = (unsigned long long) ft_atoi(neg_num_str);
	pos_num = (unsigned long long) ft_atoi(num_str);
	if (ft_strlen(num_str) > 19 || pos_num > to_compare)
	{
		*exit_status = 255;
		joined = ft_strjoin(neg_num_str, ": numeric argument required");
		print_error_msg(joined, "exit");
		free(joined);
	}
	else
		*exit_status = neg_num % 256;
}

static void	positive_number_exit(unsigned int *exit_status, char *num_str)
{
	unsigned long long	unum;
	char				*joined;
	int					len;

	len = ft_strlen(num_str);
	if (*num_str == '+')
	{
		unum = (unsigned long long) ft_atoi(num_str + 1);
		len--;
	}
	else
		unum = (unsigned long long) ft_atoi(num_str);
	if (len > 19 || unum > LLONG_MAX)
	{
		*exit_status = 255;
		joined = ft_strjoin(num_str, ": numeric argument required");
		print_error_msg(joined, "exit");
		free(joined);
	}
	else
		*exit_status = unum % 256;
}

unsigned int	shell_exit(char **av, unsigned int *exit_status, \
	int p_count)
{
	int				i;

	i = 0;
	while (av[i] != NULL)
		i++;
	if (p_count == 0)
		ft_putstr_fd("exit\n", 1);
	not_valid_arg(exit_status, av[1]);
	if ((p_count == 0 && i == 2) || (p_count == 0 && i > 2 \
		&& *exit_status == 255))
		exit(*exit_status);
	if (i > 2 && av[1] && !(*exit_status == 255))
	{
		print_error_msg("too many arguments", "exit");
		*exit_status = 1;
	}
	return (*exit_status);
}

static void	not_valid_arg(unsigned int *temp_exit_status, char *num_str)
{
	char	*joined;

	if (num_str)
	{
		if (ft_str_is_numeric(num_str + 1) == 0 || (!(*num_str == '+' || \
		*num_str == '-') && ft_str_is_numeric(num_str) == 0) || \
		((*num_str == '+' || *num_str == '-') && ft_strlen(num_str) == 1))
		{
			*temp_exit_status = 255;
			joined = ft_strjoin(num_str, ": numeric argument required");
			print_error_msg(joined, "exit");
			free(joined);
		}
		else if (ft_strchr(num_str, '-') != NULL)
			negative_number_exit(temp_exit_status, num_str + 1, num_str);
		else
			positive_number_exit(temp_exit_status, num_str);
	}
}
