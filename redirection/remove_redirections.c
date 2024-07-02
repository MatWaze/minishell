/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:25:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 14:04:01 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "expansion/expansion_constants.h"
#include "export/t_export.h"
#include "libft/libft.h"
#include "t_fd.h"
#include "quotes/quotes.h"

int					heredoc(char *del, t_fd *fds);
char				*get_redir_arg(const char **str, t_export **evl, int error,
						int mask);
int					count_cmd_str(const char *str, size_t *size,
						t_export **evl);

const char			*read_from_file(const char *str, t_fd *fds, t_export **evl,
						int error);
const char			*write_to_file(const char *str, t_fd *fds, t_export **evl,
						int error);
const char			*append_to_file(const char *str, t_fd *fds, t_export **evl,
						int error);

static const char	*redirect(const char *str, t_fd *fds, t_export **evl,
						int error);
static void			initialize(char **cmd, char ***splitted_cmd, size_t *i,
						t_fd *p);

char	**remove_redirections(const char *str, t_fd *fds, t_export **evl,
			int error)
{
	char	*cmd;
	char	**splitted_cmd;
	size_t	cmd_size;
	size_t	i;

	initialize(&cmd, &splitted_cmd, &i, fds);
	if (!count_cmd_str(str, &cmd_size, evl))
		cmd = (char *)malloc(sizeof(char) * (cmd_size + 1));
	if (cmd)
	{
		track_quote(str, '\0', 0);
		while (str && *str)
		{
			if (!track_quote(NULL, '\0', 0) && (*str == '<' || *str == '>'))
				str = redirect(str, fds, evl, error);
			else
				cmd[i++] = *str++;
		}
		cmd[i] = '\0';
		if (str)
			splitted_cmd = quoted_split(cmd, "\t\n\v\f\r ");
		free(cmd);
	}
	return (splitted_cmd);
}

static void	initialize(char **cmd, char ***splitted_cmd, size_t *i, t_fd *p)
{
	*cmd = NULL;
	*splitted_cmd = NULL;
	*i = 0;
	p->rfd = -1;
	p->wfd = -1;
}

static const char	*redirect(const char *str, t_fd *fds, t_export **evl,
						int error)
{
	if (*str == '<' && str[1] == '<')
	{
		str += 2;
		if (heredoc(get_redir_arg(&str, evl, error,
					TILDA_MASK | ENV_ERR_MASK | ENV_EXP_MASK), fds))
			str = NULL;
	}
	else if (*str == '<')
		str = read_from_file(str + 1, fds, evl, error);
	else if (str[1] == '>')
		str = append_to_file(str + 2, fds, evl, error);
	else
		str = write_to_file(str + 1, fds, evl, error);
	return (str);
}
