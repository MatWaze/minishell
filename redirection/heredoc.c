/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:17:03 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/26 11:52:35 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft/libft.h"
#include "readline/readline.h"
#include "t_heredoc.h"
#include "common/common.h"

static void	print_error(int error);
static int	heredoc_line(const char *line, const t_hdlst **del, int fd);

int	heredoc(t_heredoc *hds)
{
	char	*line;
	int		error;
	t_hdlst	*del;

	hds->fd = open("/tmp/minishell_here-document.txt", O_WRONLY | O_CREAT,
			S_IWUSR + S_IRUSR);
	error = hds->fd == -1;
	del = hds->hdlst;
	while (!error && del)
	{
		line = readline("> ");
		if (line)
		{
			error = heredoc_line(line, (const t_hdlst **)&del, hds->fd);
			free(line);
		}
		else
			error = 1;
	}
	if (hds->fd != -1)
		close(hds->fd);
	ft_lstclear((t_list **)&hds->hdlst, free);
	if (!error)
		hds->fd = open("/tmp/minishell_here-document.txt", O_RDONLY);
	print_error(error);
	return (error || hds->fd == -1);
}

static int	heredoc_line(const char *line, const t_hdlst **del, int fd)
{
	size_t	size;
	ssize_t	wrote;
	int		error;

	size = ft_strlen(line);
	if (size == ft_strlen((*del)->str)
		&& !ft_strncmp((*del)->str, line, size))
	{
		*del = (*del)->next;
		error = 0;
	}
	else
	{
		wrote = write(fd, line, size);
		error = (wrote == -1 || (size_t)wrote != size) * 2;
		if (!error)
		{
			wrote = write(fd, "\n", 1);
			error = (wrote == -1 || (size_t)wrote != 1) * 2;
		}
	}
	return (error);
}

static void	print_error(int error)
{
	if (errno)
		print_error_msg(strerror(errno), "<<");
	else if (error == 1)
		print_error_msg("here-document delimited by end-of-file",
			"warning");
	else if (error == 2)
		print_error_msg("can't write to temporary file", "<<");
}
