/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:10:19 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/05 12:14:09 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"
#include "common/common.h"
#include "t_args.h"

static int	exit_no_arguments(char *num_str, t_args *args);
static int	ft_str_is_numeric(char *str);
static void	negative_number_exit(unsigned int *exit_status, \
	char *num_str, char *neg_num_str);
static void	positive_number_exit(unsigned int *exit_status, char *num_str);

void	shell_exit(char *num_str, t_args *args)
{
	unsigned int		exit_status;
	char				*joined;

	exit_status = 0;
	if (exit_no_arguments(num_str, args) == 0)
	{
		if (args->p_count == 0)
			ft_putstr_fd("exit\n", 1);
		if (ft_str_is_numeric(num_str + 1) == 0 || \
			(!(*num_str == '+' || *num_str == '-') && \
			ft_str_is_numeric(num_str) == 0) || \
			((*num_str == '+' || *num_str == '-') && ft_strlen(num_str) == 1))
		{
			exit_status = 255;
			joined = ft_strjoin(num_str, ": numeric argument required\n");
			print_error_msg(joined, "exit");
			free(joined);
		}
		else if (ft_strchr(num_str, '-') != NULL)
			negative_number_exit(&exit_status, num_str + 1, num_str);
		else
			positive_number_exit(&exit_status, num_str);
		if (args->p_count == 0)
			exit(exit_status);
	}
}

static int	exit_no_arguments(char *num_str, t_args *args)
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

static int	ft_str_is_numeric(char *str)
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
		joined = ft_strjoin(neg_num_str, ": numeric argument required\n");
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
		joined = ft_strjoin(num_str, ": numeric argument required\n");
		print_error_msg(joined, "exit");
		free(joined);
	}
	else
		*exit_status = unum % 256;
}
