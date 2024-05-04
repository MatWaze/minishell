/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:21:40 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/23 16:26:43 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c);
static int	ft_isupper(int c);

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

static int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

static int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}
