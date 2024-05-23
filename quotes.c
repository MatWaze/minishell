/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:37:29 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/22 20:09:51 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	quotes_type(const char *str, const char *const pc)
{
	char	type;

	type = 0;
	while (str != pc)
	{
		if (*str == '"' || *str == '\'')
		{
			if (!type)
				type = *str;
			else if (type == *str)
				type = 0;
		}
	}
	return (type);
}

int	are_quotes_closed(const char *str)
{
	char	type;

	type = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			if (!type)
				type = *str;
			else if (type == *str)
				type = 0;
		}
	}
	return (!type);
}
