/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:25:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/20 10:28:10 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "libft/libft.h"
#include "t_fd.h"
#include "t_env_exp.h"
#include "quotes/quotes.h"
#include "t_hdlst.h"

char				*get_redir_arg(const char **str, t_export **evl, int error);
int					count_cmd_str(const char *str, size_t *size);
static const char	*heredoc_delimeter(const char *str, t_hdlst **dels,
						t_env_exp *env_exp);
const char			*read_from_file(const char *str, t_fd *fds,
						t_env_exp *env_exp);
const char			*write_to_file(const char *str, t_fd *fds, int oflags,
						t_env_exp *env_exp);

static const char	*redirect(const char *str, t_fd *fds, t_hdlst **dels,
						t_env_exp *env_exp);
static void			initialize(t_hdlst **dels, char **cmd, char ***splitted_cmd,
						size_t *i);

char	**remove_redirections(const char *str, t_fd *fds, t_hdlst **dels,
			t_env_exp *env_exp)
{
	char	*cmd;
	char	**splitted_cmd;
	size_t	cmd_size;
	size_t	i;

	initialize(dels, &cmd, &splitted_cmd, &i);
	if (count_cmd_str(str, &cmd_size))
		cmd = (char *)malloc(sizeof(char) * (cmd_size + 1));
	if (cmd)
	{
		track_quote(str, '\0', 0);
		while (str && i < cmd_size)
		{
			if (!track_quote(NULL, '\0', 0) && (*str == '<' || *str == '>'))
				str = redirect(str, fds, dels, env_exp);
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

static void	initialize(t_hdlst **dels, char **cmd, char ***splitted_cmd,
				size_t *i)
{
	*dels = NULL;
	*cmd = NULL;
	*splitted_cmd = NULL;
	*i = 0;
}

static const char	*redirect(const char *str, t_fd *fds, t_hdlst **dels,
						t_env_exp *env_exp)
{
	if (*str == '<' && str[1] == '<')
		str = heredoc_delimeter(str + 2, dels, env_exp);
	else if (*str == '<')
		str = read_from_file(str + 1, fds, env_exp);
	else if (str[1] == '>')
		str = write_to_file(str + 2, fds, O_APPEND, env_exp);
	else
		str = write_to_file(str + 1, fds, 0, env_exp);
	return (str);
}

static const char	*heredoc_delimeter(const char *str, t_hdlst **dels,
						t_env_exp *env_exp)
{
	t_list	*new;
	char	*arg;

	arg = get_redir_arg(&str, env_exp->evl, env_exp->error);
	if (arg)
	{
		new = ft_lstnew(arg);
		if (new)
			ft_lstadd_back((t_list **)dels, new);
		else
		{
			free(arg);
			str = NULL;
		}
	}
	else
		str = NULL;
	return (str);
}
