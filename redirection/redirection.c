/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:25:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/13 13:32:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "t_fd.h"
#include "quotes/quotes.h"
#include "t_hdlst.h"

char		*extract_ev(const char **pstr);

static int	count_cmd_str(const char *str, size_t *size);
static int	ft_isspace(unsigned char c);
static int	validate_arg(const char *str);

char	**remove_redirections(const char *str, t_fd *fds, t_hdlst **dels)
{
	char	*cmd;

	*dels = NULL;
}

static int	count_cmd_str(const char *str, size_t *size)
{
	int		error;

	*size = 0;
	error = 0;
	track_quote(str, '\0', 0);
	while (!error && *str)
	{
		if (!track_quote(NULL, '\0', 0) && (*str == '<' || *str == '>'))
		{
			if (*str == '<' && str[1] == '<' || *str == '>' && str[1] == '>')
				str++;
			str++;
			while (ft_isspace(*str))
				str++;
			track_quote(str, '\0', 0);
		}
		*size += 1;
	}
	return (error);
}

static int	ft_isspace(unsigned char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

static int	validate_arg(const char *str)
{
	int	error;

	error = 0;
	if (*str == '$' && str[1] && !ft_isspace(str[1])&& str[1] != '<'
		&& str[1] != '>' && str[1] != '\'' && str[1] != '"' && str[1] != '\'')
}
