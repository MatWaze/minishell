/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:00:36 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 16:38:42 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "export/export.h"
#include "expansion/expansion.h"
#include "libft/libft.h"
#include "quotes/quotes.h"
#include "common/common.h"

char		*extract_ev(const char **pstr);

static int	validate_arg(const char **str, t_export **evl);
static void	pass_spaces(const char **str);
static void	pass_until_arg_end(const char **str);

int	count_cmd_str(const char *str, size_t *size, t_export **evl)
{
	int			error;
	static char	red_sign[3] = {0};

	*size = 0;
	error = 0;
	track_quote(str, '\0', 0);
	while (!error && *str)
	{
		if (!track_quote(NULL, '\0', 0) && (*str == '<' || *str == '>'))
		{
			red_sign[0] = *str;
			if ((*str == '<' && str[1] == '<')
				|| (*str == '>' && str[1] == '>'))
			{
				str++;
				red_sign[1] = *str;
			}
			else
				red_sign[1] = '\0';
			track_quote(++str, '\0', 0);
			pass_spaces(&str);
			if (!*str || *str == '<' || *str == '>')
				print_error_msg("operator has no argument\n", red_sign);
			error = !*str || *str == '<' || *str == '>'
				|| (!red_sign[1] && validate_arg(&str, evl));
			*size -= 1;
		}
		else
			str++;
		*size += 1;
	}
	return (error);
}

static int	validate_arg(const char **str, t_export **evl)
{
	int		error;
	char	*error_msg;
	char	*var;

	error = 0;
	var = NULL;
	if (**str == '$' && str[0][1] && !ft_strchr("\t\n\v\f\r <>'\"", str[0][1]))
	{
		var = extract_ev(str);
		error = var == NULL || (get_value_from_key(evl, var) == NULL
				&& (!str[0][1] || ft_strchr("\t\n\v\f\r <>", str[0][1])));
		track_quote(++(str[0]), '\0', 0);
	}
	if (error)
	{
		error_msg = ft_strjoin("$", var);
		if (error_msg)
			print_error_msg("ambiguous redirect\n", error_msg);
		free(error_msg);
	}
	else
		pass_until_arg_end(str);
	free(var);
	return (error);
}

static void	pass_until_arg_end(const char **str)
{
	while (str[0][0] && (track_quote(NULL, '\0', 1)
			|| !ft_strchr("\t\n\v\f\r <>", str[0][0])))
	{
		str[0]++;
		track_quote(NULL, '\0', 0);
	}
}

static void	pass_spaces(const char **str)
{
	while (str[0][0] && !track_quote(NULL, '\0', 1)
			&& ft_strchr("\t\n\v\f\r ", str[0][0]))
	{
		str[0]++;
		track_quote(NULL, '\0', 0);
	}
}

char	*get_redir_arg(const char **str, t_export **evl, int error, int mask)
{
	const char	*tstr;
	char		*arg;
	size_t		arg_size;

	pass_spaces(str);
	tstr = *str;
	pass_until_arg_end(str);
	arg_size = *str - tstr;
	arg = (char *)malloc(sizeof(char) * (arg_size + 1));
	if (arg)
	{
		ft_strlcpy(arg, tstr, arg_size + 1);
		tstr = expand(arg, evl, error, mask);
		free(arg);
		arg = (char *)tstr;
	}
	return (arg);
}
