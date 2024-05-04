/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:36:03 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/29 16:46:22 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_digit(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n = -n;
			write(fd, "-", 1);
		}
		print_digit(n, fd);
	}
}

void	print_digit(int n, int fd)
{
	char	d;

	d = n % 10 + '0';
	n /= 10;
	if (n)
		print_digit(n, fd);
	write(fd, &d, 1);
}
