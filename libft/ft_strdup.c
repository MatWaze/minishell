/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:19:59 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/25 20:45:48 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*ret;
	char	*p;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	p = ret;
	if (p)
	{
		while (*src)
			*p++ = *src++;
		*p = 0;
	}
	return (ret);
}
