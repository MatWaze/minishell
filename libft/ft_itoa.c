/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:09:31 by zanikin           #+#    #+#             */
/*   Updated: 2024/02/14 20:19:46 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	num_places(int n);
static void	ft_output(char *out, int n, int places);
static int	num_places_pos(int n);

char	*ft_itoa(int n)
{
	char	*result;
	int		places;

	if (n == -2147483648)
		result = ft_strdup("-2147483648");
	else
	{
		places = num_places(n);
		result = (char *)malloc(places + 1);
		if (result)
			ft_output(result, n, places);
	}
	return (result);
}

static int	num_places_pos(int n)
{
	int	count;

	if (n < 10)
		count = 1;
	else if (n < 100)
		count = 2;
	else if (n < 1000)
		count = 3;
	else if (n < 10000)
		count = 4;
	else if (n < 100000)
		count = 5;
	else if (n < 1000000)
		count = 6;
	else if (n < 10000000)
		count = 7;
	else if (n < 100000000)
		count = 8;
	else if (n < 1000000000)
		count = 9;
	else
		count = 10;
	return (count);
}

static int	num_places(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	count += num_places_pos(n);
	return (count);
}

static void	ft_output(char *out, int n, int places)
{
	int	sign;

	sign = 0;
	out[places] = '\0';
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	while (places-- - sign)
	{
		out[places] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		out[0] = '-';
}
