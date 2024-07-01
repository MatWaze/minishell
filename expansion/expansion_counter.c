/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:06:16 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/20 18:55:41 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "export/export.h"

char			*extract_ev(const char **str);
int				is_inside_quotes(char type, char *qtype);
int				digits_count(int n);

static size_t	ev_size(const char **str, t_export **ev, int error);
static size_t	count_evv_size(const char **str, t_export **evlist);

size_t	count_expanded_string(const char *str, t_export **ev, int error)
{
	size_t	esize;
	char	qtype;
	char	*tmp;

	esize = 0;
	qtype = 0;
	tmp = get_value_from_key(ev, "HOME");
	if (*str == '~' && tmp && (!str[1] || str[1] == '/'))
	{
		esize += ft_strlen(tmp);
		str++;
	}
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			esize += is_inside_quotes(*str, &qtype);
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
		*qtype = type;
		is = 0;
	}
	else if (*qtype == type)
	{
		*qtype = 0;
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
		size = digits_count(error);
	}
	else if (!str[0][1] || str[0][1] == ' ' || str[0][1] == '$')
		size = 1;
	else
		size = count_evv_size(str, ev);
	return (size);
}

static size_t	count_evv_size(const char **str, t_export **evlist)
{
	size_t	size;
	char	*ev_name;
	char	*ev_val;

	ev_name = extract_ev(str);
	ev_val = get_value_from_key(evlist, ev_name);
	free(ev_name);
	if (ev_val)
		size = ft_strlen(ev_val);
	else
		size = 0;
	return (size);
}

char	*extract_ev(const char **pstr)
{
	const char	*str;
	size_t		size;
	char		*ev_name;

	size = 0;
	str = pstr[0] + 1;
	while (*str && *str != '\'' && *str != '"' && *str != ' ' && *str != '$')
	{
		size++;
		str++;
	}
	ev_name = (char *)malloc(sizeof(char) * (size + 1));
	if (ev_name)
	{
		str = pstr[0] + 1;
		pstr[0] = str + size - 1;
		ev_name[size] = '\0';
		while (size--)
			ev_name[size] = str[size];
	}
	return (ev_name);
}
