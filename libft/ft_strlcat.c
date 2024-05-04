/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:37:49 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/31 21:57:40 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	buff_size(size_t src_l, size_t dst_l,
					size_t size);
static size_t	ft_strlensafe(const char *str);
static size_t	ft_strlensatsafe(const char *str, size_t max, int *exceeds);

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_l;
	size_t	dst_l;
	size_t	l;
	int		exceeds;

	src_l = ft_strlensafe(src);
	dst_l = ft_strlensatsafe(dest, size, &exceeds);
	if (dest)
		dest += dst_l;
	l = buff_size(src_l, dst_l, size);
	if (dst_l <= size)
		size -= dst_l;
	else
		size = 1;
	while (*src && size > 1)
	{
		size--;
		*dest++ = *src++;
	}
	if (dest && !exceeds)
		*dest = 0;
	return (l);
}

static size_t	buff_size(size_t src_l, size_t dst_l,
		size_t size)
{
	size_t	l;

	if (src_l == 0)
	{
		if (size > dst_l)
			l = dst_l;
		else
			l = size;
	}
	else if (size >= dst_l)
		l = src_l + dst_l;
	else
		l = src_l + size;
	return (l);
}

static size_t	ft_strlensafe(const char *str)
{
	size_t	result;

	if (str)
		result = ft_strlen(str);
	else
		result = 0;
	return (result);
}

static size_t	ft_strlensatsafe(const char *str, size_t max, int *exceeds)
{
	size_t	result;

	result = 0;
	*exceeds = 0;
	if (str)
	{
		while (max-- && *str)
		{
			str++;
			result++;
		}
		*exceeds = *str;
	}
	return (result);
}
