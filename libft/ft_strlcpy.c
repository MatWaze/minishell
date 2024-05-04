/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:00:06 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/25 20:46:14 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	l;
	size_t	s;

	l = 0;
	s = 0;
	if (size)
		s = size - 1;
	while (*src && s--)
	{
		*dest++ = *src++;
		l++;
	}
	if (size)
		*dest = 0;
	while (*src++)
		l++;
	return (l);
}
