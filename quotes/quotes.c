/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin < zanikin@student.42yerevan.am>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:37:29 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/12 09:54:38 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static char	update_qtype(const char *cur, char qtype);

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
		str++;
	}
	return (type);
}

char	track_quote(const char *str, char assumed_qtype, int stop)
{
	static const char	*cur = NULL;
	static char			qtype = 0;
	static int			stopped = 0;
	char				result;

	result = '\0';
	if (stopped)
		result = qtype;
	else if (str != NULL)
	{
		cur = str;
		qtype = assumed_qtype;
	}
	else
	{
		qtype = update_qtype(cur, qtype);
		if (qtype != *cur)
			result = qtype;
		cur++;
	}
	stopped = stop;
	return (result);
}

static char	update_qtype(const char *cur, char qtype)
{
	if (*cur == '\'' || *cur == '"')
	{
		if (!qtype)
			qtype = *cur;
		else if (qtype == *cur)
			qtype = 0;
	}
	return (qtype);
}
