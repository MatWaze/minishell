/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:17:03 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/18 16:01:13 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"
#include "readline/readline.h"
#include "t_hdlst.h"
#include "common/common.h"

static int	print_error(void);

void	heredoc(t_hdlst **pdels)
{
	char	*line;
	int		error;
	size_t	size;
	t_hdlst	*dels;

	error = 0;
	dels = *pdels;
	while (!error && dels)
	{
		line = readline("> ");
		if (line)
		{
			size = ft_strlen(line);
			if (size == ft_strlen(dels->str) && !ft_strncmp(dels->str, line,
					size))
				dels = dels->next;
			else
				printf("%s\n", line);
			free(line);
		}
		else
			error = print_error();
	}
	ft_lstclear((t_list **)pdels, free);
	*pdels = NULL;
}

static int	print_error(void)
{
	print_error_msg("here-document delimited by end-of-file",
		"warning");
	return (1);
}
