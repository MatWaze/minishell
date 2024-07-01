/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_args.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:18:31 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/01 21:46:12 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ARGS_H
# define T_ARGS_H
# include "export/t_export.h"
# include "libft/libft.h"

typedef struct s_args
{
	char		**argv;
	char		**envp;
	int			p_count;
	int			hd_count;
	int			j;
	char		**my_envp;
	int			quotes_closed;
	int			exit_code;
	t_list		*pids;
	t_export	*export_list;
	t_export	*env_list;
}		t_args;
#endif
