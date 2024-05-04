/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:57:48 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/29 15:47:35 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_char_from_set(char c, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	size;

	result = NULL;
	if (s1)
	{
		if (!set)
			set = "";
		while (*s1 && is_char_from_set(*s1, set))
			s1++;
		size = ft_strlen(s1);
		while (size && is_char_from_set(s1[size - 1], set))
			size--;
		result = (char *)malloc(size + 1);
		if (result)
		{
			ft_memcpy(result, s1, size);
			result[size] = '\0';
		}
	}
	return (result);
}

static int	is_char_from_set(char c, const char *set)
{
	int	found;

	found = 0;
	while (*set && found == 0)
		found = c == *set++;
	return (found);
}
