/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_exp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:48:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/15 10:52:23 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENV_EXP
# define T_ENV_EXP
# include "export/t_export.h"

typedef struct s_env_exp
{
	t_export	**evl;
	int			error;
}	t_env_exp;
#endif
