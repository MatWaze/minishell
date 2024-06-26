/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:46 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/26 12:36:11 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>

#include "export/t_export.h"
#include "common/common.h"
#include "t_fd.h"

char				*get_redir_arg(const char **str, t_export **evl, int error);

static const char	*rw(const char *str, int *fd, char *arg, int flags);

const char	*read_from_file(const char *str, t_fd *fds, t_export **evl,
				int error)
{
	return (rw(str, &fds->rfd, get_redir_arg(&str, evl, error),
			O_RDONLY));
}

const char	*write_to_file(const char *str, t_fd *fds, t_export **evl,
				int error)
{
	return (rw(str, &fds->wfd, get_redir_arg(&str, evl, error),
			O_WRONLY | O_CREAT));
}

const char	*append_to_file(const char *str, t_fd *fds, t_export **evl,
				int error)
{
	return (rw(str, &fds->wfd, get_redir_arg(&str, evl, error),
			O_APPEND | O_CREAT));
}

static const char	*rw(const char *str, int *fd, char *arg, int flags)
{
	int		nfd;

	if (arg)
	{
		nfd = open(arg, flags, (S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
		if (nfd < 0)
		{
			print_error_msg(strerror(errno), arg);
			str = NULL;
		}
		else
		{
			if (*fd != -1)
				close(*fd);
			*fd = nfd;
		}
		free(arg);
	}
	else
		str = NULL;
	return (str);
}
