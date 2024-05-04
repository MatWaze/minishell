/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:58:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/29 16:41:08 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(unsigned char c);

int	ft_atoi(const char *str)
{
	int		num;
	char	sign;

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
