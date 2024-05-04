/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:01:45 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/29 16:43:03 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isupper(int c);

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}

static int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}
