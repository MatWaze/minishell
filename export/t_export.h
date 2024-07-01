/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:13:04 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/03 11:48:31 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXPORT_H
# define T_EXPORT_H
# include "t_keyval.h"

typedef struct s_export
{
	t_keyval		*pair;
	struct s_export	*next;
}	t_export;
#endif
