/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:49:32 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/05 17:04:05 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"
#include "export/export.h"

size_t		count_expanded_string(const char *str, t_export **ev,
				int error);
int			is_inside_quotes(char type, char *qtype);
char		*extract_ev(const char **pstr);
void		insert_number(char *dst, int n);
int			digits_count(int n);
char		*expand(const char *str, t_export **evlist, int error);

static void	expand_envvar(const char **pstr, char **exp_str,
				t_export **evlist, int error);
static void	insert_envvar_val(const char **pstr, char **exp_str,
				t_export **evlist);
static void	expand_loop(const char *str, char *exp_str, t_export **evlist,
				int error);

int	expand_list(char **strs, t_export **evlist, int error)
{
	int		expanded;
	size_t	i;
	char	*str;

	i = 0;
	expanded = 1;
	while (strs[i] && expanded)
	{
		str = expand(strs[i], evlist, error);
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

char	*expand(const char *str, t_export **evlist, int error)
{
	char	*exp_str;
	char	*home;
	size_t	exp_str_size;

	exp_str_size = count_expanded_string(str, evlist, error);
	exp_str = (char *)malloc(sizeof(char) * (exp_str_size + 1));
	if (exp_str)
	{
		if (*str == '~' && (!str[1] || str[1] == '/'))
		{
			home = get_value_from_key(evlist, "HOME");
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
