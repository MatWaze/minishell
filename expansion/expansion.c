/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:49:32 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/27 15:32:08 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

size_t	count_expanded_string(const char *str, t_export **ev,
			int error);
int		is_inside_quotes(char type, char *qtype);

char	*expand(const char *str, t_export **evlist, int error)
{
	char	qtype;
	char	*exp_str;
	size_t	exp_str_size;
	char	*tmp;

	exp_str_size = count_expanded_string(str, evlist, error);
	exp_str = (char *)malloc(sizeof(char) * (exp_str_size + 1));
	qtype = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (is_inside_quotes(*str, &qtype))
				*exp_str++ = *str;
		}
		else if (!qtype && *str == '~' && (str[1] == ' ' || str[1] == '/'
				|| !str[1]))
		{
			tmp = get_value_from_key(evlist, "HOME");
			exp_str += ft_strlcpy(exp_str, tmp, ft_strlen(tmp) + 1);
		}
		else if (*str == '$' && (!qtype || qtype == '"'))
		{
			tmp = extract_ev(&str);
			
		}
		str++;
	}
}

char	*extract_ev(const char **pstr)
{
	char	*str;
	size_t	size;
	char	*ev_name;

	size = 0;
	str = pstr[0];
	while (*str && *str != '\'' && *str != '"' && *str != ' ' && *str != '$')
	{
		size++;
		str++;
	}
	ev_name = (char *)malloc(sizeof(char) * (size + 1));
	if (ev_name)
	{
		str = pstr[0];
		while (size--)
			*ev_name++ = *str++;
		ev_name = '\0';
		pstr[0] = str;
	}
	return (ev_name);
}
