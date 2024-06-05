/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:10:19 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/05 12:25:49 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/common.h"
#include "t_args.h"

static int	ft_str_is_numeric(char *str);

void	shell_exit(char *num_str)
{
	unsigned long long	unum;
	long long			num;
	unsigned int		exit_status;

	num = ft_atoi(num_str);
	unum = (unsigned long long) num;
	if (!num_str)
		exit(0);
	if (ft_str_is_numeric(num_str) == 0 || \
		(ft_strlen(num_str) > 19 || unum > LONG_MAX))
	{
		print_error_msg("numeric argument required\n", "exit");
		exit_status = 255;
	}
	else if (num < 0)
		exit_status = unum % 256;
	else
		exit_status = num % 256;
	ft_putstr_fd("exit\n", 1);
	exit(exit_status);
}

static int	ft_str_is_numeric(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ans = 0;
			break ;
		}
		i++;
	}
	return (ans);
}
