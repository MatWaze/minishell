/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:58:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/31 13:38:13 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(unsigned char c);

long long	ft_atoi(const char *str)
{
	long long	num;
	char		sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = 1 - 2 * (*str == '-');
		str++;
	}
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - '0') * sign;
	return (num);
}

static int	ft_isspace(unsigned char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}
