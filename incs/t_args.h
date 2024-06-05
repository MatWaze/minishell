/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_args.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:18:31 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/05 15:26:15 by mamazari         ###   ########.fr       */
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
	char		**my_envp;
	int			exit_code;
	t_list		*pids;
	t_export	*export_list;
	t_export	*env_list;
}		t_args;
#endif
