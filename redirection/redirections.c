/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:46 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/20 10:26:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>

#include "t_env_exp.h"
#include "t_hdlst.h"
#include "common/common.h"
#include "t_fd.h"

char				*get_redir_arg(const char **str, t_export **evl, int error);

static const char	*rw(const char *str, int *fd, t_env_exp *env_exp,
						int flags);

const char	*read_from_file(const char *str, t_fd *fds, t_env_exp *env_exp)
{
	return (rw(str, &fds->rfd, env_exp, O_RDONLY));
}

const char	*write_to_file(const char *str, t_fd *fds, int oflags,
				t_env_exp *env_exp)
{
	return (rw(str, &fds->wfd, env_exp, oflags | O_WRONLY | O_CREAT));
}

static const char	*rw(const char *str, int *fd, t_env_exp *env_exp, int flags)
{
	char	*arg;
	int		nfd;

	arg = get_redir_arg(&str, env_exp->evl, env_exp->error);
	if (arg)
	{
		nfd = open(arg, flags);
		if (nfd < 0)
			print_error_msg(strerror(errno), arg);
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
