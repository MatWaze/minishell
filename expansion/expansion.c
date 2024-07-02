/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:49:32 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/01 22:58:38 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "export/export.h"

size_t		count_expanded_string(const char *str, t_export **ev,
				int error, int mask);
int			is_inside_quotes(char type, char *qtype);
char		*extract_ev(const char **pstr);
void		insert_number(char *dst, int n);
int			digits_count(int n);
char		*expand(const char *str, t_export **evlist, int error, int mask);

static void	expand_envvar(const char **pstr, char **exp_str,
				t_export **evlist, int error);
static void	insert_envvar_val(const char **pstr, char **exp_str,
				t_export **evlist);
static void	expand_loop(const char *str, char *exp_str, t_export **evlist,
				int error);

int	expand_list(char **strs, t_export **evlist, int error, int mask)
{
	int		expanded;
	size_t	i;
	char	*str;

	i = 0;
	expanded = strs != NULL;
	while (expanded && strs[i])
	{
		str = expand(strs[i], evlist, error, mask);
		if (str)
		{
			free(strs[i]);
			strs[i++] = str;
		}
		else
			expanded = 0;
	}
	return (expanded);
}

char	*expand(const char *str, t_export **evlist, int error, int mask)
{
	char	*exp_str;
	char	*home;
	size_t	exp_str_size;

	exp_str_size = count_expanded_string(str, evlist, error, mask);
	exp_str = (char *)malloc(sizeof(char) * (exp_str_size + 1));
	if (exp_str)
	{
		home = get_value_from_key(evlist, "HOME");
		if (*str == '~' && home && (!str[1] || str[1] == '/'))
		{
			expand_loop(str + 1, exp_str + ft_strlcpy(exp_str, home,
					ft_strlen(home) + 1), evlist, error);
		}
		else
			expand_loop(str, exp_str, evlist, error);
	}
	return (exp_str);
}

static void	expand_loop(const char *str, char *exp_str, t_export **evlist,
				int error)
{
	char	qtype;

	qtype = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (is_inside_quotes(*str, &qtype))
				*exp_str++ = *str;
		}
		else if (*str == '$' && (!qtype || qtype == '"'))
			expand_envvar(&str, &exp_str, evlist, error);
		else
			*exp_str++ = *str;
		str++;
	}
	*exp_str = '\0';
}

static void	expand_envvar(const char **pstr, char **exp_str,
					t_export **evlist, int error)
{
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
		insert_number(exp_str[0], error);
		exp_str[0] += digits_count(error);
	}
	else if (!pstr[0][1] || pstr[0][1] == ' ' || pstr[0][1] == '$')
		exp_str[0]++[0] = '$';
	else
		insert_envvar_val(pstr, exp_str, evlist);
}

static void	insert_envvar_val(const char **pstr, char **exp_str,
				t_export **evlist)
{
	char	*name;
	char	*env;

	name = extract_ev(pstr);
	env = get_value_from_key(evlist, name);
	free(name);
	if (env)
		exp_str[0] += ft_strlcpy(exp_str[0], env, ft_strlen(env) + 1);
}
