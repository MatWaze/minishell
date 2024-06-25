/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_args.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:18:31 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/23 02:21:41 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ARGS_H
# define T_ARGS_H
# include "export/t_export.h"
# include "redirection/t_heredoc.h"
# include "libft/libft.h"

typedef struct s_args
{
	char		**argv;
	char		**envp;
	int			p_count;
	char		**my_envp;
	int			exit_code;
	t_list		*pids;
	t_heredoc	hds;
	t_export	*export_list;
	t_export	*env_list;
}		t_args;
#endif
