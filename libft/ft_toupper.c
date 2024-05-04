/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:53:41 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/29 16:42:33 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c);

int	ft_toupper(int c)
{
	if (ft_islower(c))
		c -= 32;
	return (c);
}

static int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}
