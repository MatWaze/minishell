/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin < zanikin@student.42yerevan.am>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:25:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/10 15:08:46 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "t_fd.h"
#include "quotes/quotes.h"
#include "t_hdlst.h"

static int	count_cmd_str(const char *str, size_t *size);

char	**remove_redirections(const char *str, t_fd *fds, t_hdlst **dels)
{
	char	*cmd;

	*dels = NULL;
}

static int	count_cmd_str(const char *str, size_t *size)
{
	int	needs_arg;
	int	error;

	*size = 0;
	error = 0;
	needs_arg = 0;
	while (*str)
	{

	}
	return (error);
}
