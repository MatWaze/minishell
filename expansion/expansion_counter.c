/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:06:16 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/27 14:45:48 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*extract_ev(const char **str);
int				is_inside_quotes(char type, char *qtype);
static size_t	ev_size(const char **str, t_export **ev, int error);
static size_t	count_evv_size(const char *str, t_export **evlist);

size_t	count_expanded_string(const char *str, t_export **ev, int error)
{
	size_t	esize;
	char	qtype;

	esize = 0;
	qtype = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			esize += is_inside_quotes(*str, &qtype);
		else if (!qtype && *str == '~' && (str[1] == ' ' || str[1] == '/'
				|| !str[1]))
			esize += ft_strlen(get_value_from_key(ev, "HOME"));
		else if (*str == '$' && (!qtype || qtype == '"'))
			esize += ev_size(&str, ev, error);
		else
			esize++;
		str++;
	}
	return (esize);
}

int	is_inside_quotes(char type, char *qtype)
{
	int	is;

	if (!*qtype)
	{
		qtype = type;
		is = 0;
	}
	else if (qtype == type)
	{
		qtype = 0;
		is = 0;
	}
	else
		is = 1;
	return (is);
}

static size_t	ev_size(const char **str, t_export **ev, int error)
{
	size_t	size;
	char	type;

	if (str[0][1] == '\'' || str[0][1] == '"')
	{
		size = 0;
		type = (++str[0])[0];
		while ((++str[0])[0] != type)
			size++;
	}
	else if (str[0][1] == '?')
	{
		str[0]++;
		size = error <= 0;
		while (error)
		{
			error /= 10;
			size++;
		}
	}
	else if (!str[0][0] || str[0][0] == ' ' || str[0][0] == '$')
		size = 1;
	else
		size = count_evv_size(str, ev);
	return (size);
}

static size_t	count_evv_size(const char *str, t_export **evlist)
{
	size_t	size;
	char	*ev_name;

	ev_name = extract_ev(str);
	size = ft_strlen(get_value_from_key(evlist, ev_name));
	free(ev_name);
	return (size);
}
