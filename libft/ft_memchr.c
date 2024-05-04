/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:26:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/30 14:35:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	const void			*r;

	r = 0;
	str = s;
	if (n)
	{
		while (n && !r)
		{
			if (*str == (unsigned char)c)
				r = str;
			str++;
			n--;
		}
	}
	return ((void *)r);
}
