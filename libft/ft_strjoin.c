/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:39:07 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/29 16:44:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_safestrlen(const char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	size1;
	size_t	size2;

	size1 = ft_safestrlen(s1);
	size2 = ft_safestrlen(s2);
	result = (char *)malloc(size1 + size2 + 1);
	if (result)
	{
		ft_memcpy(result, s1, size1);
		ft_memcpy(result + size1, s2, size2 + 1);
	}
	return (result);
}

static size_t	ft_safestrlen(const char *str)
{
	size_t	result;

	if (str)
		result = ft_strlen(str);
	else
		result = 0;
	return (result);
}
