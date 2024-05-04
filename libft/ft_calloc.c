/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:24:42 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/30 17:03:48 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = 0;
	if (count == 0 || 18446744073709551615ul / count >= size)
	{
		mem = malloc(count * size);
		if (mem)
			ft_memset(mem, 0, count * size);
	}
	return (mem);
}
