/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:46 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/29 03:36:53 by zanikin          ###   ########.fr       */
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

char		*get_redir_arg(const char **str, t_export **evl, int error);

static int	rw(const char *str, int *fd, char *arg, int flags);

const char	*read_from_file(const char *str, t_fd *fds, t_export **evl,
				int error)
{
	char	*arg;

	arg = get_redir_arg(&str, evl, error);
	if (rw(str, &fds->rfd, arg, O_RDONLY))
		str = NULL;
	return (str);
}

const char	*write_to_file(const char *str, t_fd *fds, t_export **evl,
				int error)
{
	char	*arg;

	arg = get_redir_arg(&str, evl, error);
	if (rw(str, &fds->wfd, arg, O_WRONLY | O_CREAT))
		str = NULL;
	return (str);
}

const char	*append_to_file(const char *str, t_fd *fds, t_export **evl,
				int error)
{
	char	*arg;

	arg = get_redir_arg(&str, evl, error);
	if (rw(str, &fds->wfd, arg, O_APPEND | O_CREAT))
		str = NULL;
	return (str);
}

static int	rw(const char *str, int *fd, char *arg, int flags)
{
	int	nfd;

	nfd = -1;
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
	return (nfd == -1);
}
