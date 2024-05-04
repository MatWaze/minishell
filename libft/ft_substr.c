/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:53:22 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/30 14:53:39 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	act_size;
	char	*result;

	result = NULL;
	if (s)
	{
		act_size = ft_strlen(s);
		if (start > act_size)
			start = act_size;
		if (len < act_size - start)
			act_size = len;
		else
			act_size -= start;
		result = (char *)malloc(act_size + 1);
		if (result)
		{
			ft_memcpy(result, s + start, act_size);
			result[act_size] = '\0';
		}
	}
	return (result);
}
