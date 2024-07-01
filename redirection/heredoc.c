/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:17:03 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/01 17:44:40 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft/libft.h"
#include "quotes/quotes.h"
#include "readline/readline.h"
#include "t_fd.h"
#include "common/common.h"

static void	print_error(int error);
static int	heredoc_line(const char *line, const char *del, int *ended, int fd);
static void	replace_fd(int wfd, int *fd, int error);

int	count_heredoc(const char **pipes)
{
	int		count;
	int		stop;
	char	*hd;
	int		i;

	count = 0;
	i = 0;
	while (pipes[i])
	{
		stop = 0;
		hd = ft_strnstr(pipes[i], "<<", ft_strlen(pipes[i]));
		while (hd && !stop)
		{
			stop = !quotes_type(pipes[i], hd);
			if (!stop)
				hd = ft_strnstr(hd + 2, "<<", ft_strlen(hd + 2));
		}
		count += stop;
		i++;
	}
	return (count);
}

int	heredoc(char *del, t_fd *fds)
{
	char	*line;
	int		error;
	int		fd;
	int		ended;

	fd = open("/tmp/minishell_here-document.txt", O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR + S_IRUSR);
	error = fd == -1;
	ended = 0;
	while (!(error || ended))
	{
		ft_putstr_fd("> ", fds->tempout);
		line = get_next_line(fds->tempin);
		if (line)
		{
			error = heredoc_line(line, del, &ended, fd);
			free(line);
		}
		else
			error = 1;
	}
	write(fds->hdfd[1], "a", 1);
	free(del);
	replace_fd(fd, &fds->rfd, error);
	print_error(error);
	return (error || fds->rfd == -1);
}

static int	heredoc_line(const char *line, const char *del, int *ended, int fd)
{
	size_t	size;
	ssize_t	wrote;
	int		error;

	size = ft_strlen(line) - 1;
	if (size == ft_strlen(del)
		&& !ft_strncmp(del, line, size))
	{
		*ended = 1;
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

static void	replace_fd(int wfd, int *fd, int error)
{
	if (wfd != -1)
		close(wfd);
	if (!error)
		*fd = open("/tmp/minishell_here-document.txt", O_RDONLY);
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
