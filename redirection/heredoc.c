/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:17:03 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/25 07:32:33 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft/libft.h"
#include "readline/readline.h"
#include "t_heredoc.h"
#include "common/common.h"

static void	print_error(int error);

int	heredoc(t_heredoc *hds)
{
	char	*line;
	int		error;
	size_t	size;
	ssize_t	wrote;

	error = pipe(hds->fd);
	while (!error && hds->hdlst)
	{
		line = readline("> ");
		if (line)
		{
			size = ft_strlen(line);
			if (size == ft_strlen(hds->hdlst->str)
				&& !ft_strncmp(hds->hdlst->str, line, size))
				hds->hdlst = hds->hdlst->next;
			else
			{
				wrote = write(hds->fd[1], line, size);
			}
			free(line);
		}
		else
			error = 1;
	}
	ft_lstclear((t_list **)&hds->hdlst, free);
	print_error(error);
	return (error);
}

static void	print_error(int error)
{
	if (errno)
		print_error_msg(strerror(errno), "<<");
	else if (error == 1)
		print_error_msg("here-document delimited by end-of-file",
			"warning");
}
