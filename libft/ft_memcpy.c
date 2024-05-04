/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:02:40 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/28 23:15:21 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_str;
	const char	*src_str;

	if (dst || src)
	{
		src_str = src;
		dst_str = dst;
		while (n--)
			*dst_str++ = *src_str++;
	}
	return (dst);
}
