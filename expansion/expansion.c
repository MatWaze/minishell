/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:49:32 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/27 20:52:17 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

size_t		count_expanded_string(const char *str, t_export **ev,
				int error);
int			is_inside_quotes(char type, char *qtype);
static void	expand_envvar(const char **pstr, char **exp_str,
				t_export **evlist, int error);
static void	insert_envvar_val(const char **pstr, char **exp_str,
				t_export **evlist);

char	**expand_list(const char **strs, t_export **evlist, int error)
{
	char	**exp_strs;
	size_t	count;

	count = 0;
	while (strs[count])
		count++;
	exp_strs = (char **)malloc(sizeof(char *) * (count + 1));
	exp_strs[count] = NULL;
	count = 0;
	if (strs[0])
		exp_strs[count++] = expand(strs[0], evlist, error);
	while (strs[count] && strs[count - 1])
	{
		exp_strs[count] = expand(strs[count], evlist, error);
		count++;
	}
	return (exp_strs);
}

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
		if ((*str == '\'' || *str == '"') && is_inside_quotes(*str, &qtype))
			*exp_str++ = *str;
		else if (!qtype && *str == '~' && (str[1] == ' ' || str[1] == '/'
				|| !str[1]))
		{
			tmp = get_value_from_key(evlist, "HOME");
			exp_str += ft_strlcpy(exp_str, tmp, ft_strlen(tmp) + 1);
		}
		else if (*str == '$' && (!qtype || qtype == '"'))
			expand_envvar(&str, &exp_str, evlist, error);
		else
			*exp_str++ = *str;
		str++;
	}
	return (exp_str);
}

static void	expand_envvar(const char **pstr, char **exp_str,
					t_export **evlist, int error)
{
	char	*tmp;
	char	type;

	if (pstr[0][1] == '\'' || pstr[0][1] == '"')
	{
		type = (++pstr[0])[0];
		while ((++pstr[0])[0] != type)
			exp_str[0]++[0] = pstr[0][0];
	}
	else if (pstr[0][1] == '?')
	{
		pstr[0]++;
		if (error <= 0)
			exp_str[0]++[0] = '0' * (!error) + '-' * (error < 0);
		while (error)
		{
			exp_str[0]++[0] = (error % 10) * (1 - 2 * (error < 0)) + '0';
			error /= 10;
		}
	}
	else if (!pstr[0][0] || pstr[0][0] == ' ' || pstr[0][0] == '$')
		exp_str[0]++[0] = '$';
	else
		insert_envvar_val(pstr, exp_str, evlist);
}

static void	insert_envvar_val(const char **pstr, char **exp_str,
				t_export **evlist)
{
	char	*name;

	name = extract_ev(pstr);
	exp_str[0] += ft_strlcpy(exp_str[0], name,
			ft_strlen(get_value_from_key(evlist, name)) + 1);
	free(name);
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
