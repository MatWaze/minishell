/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:13:04 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/01 10:50:57 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXPORT_H
# define T_EXPORT_H
# include "t_content.h"

typedef struct s_export
{
	t_content		*pair;
	struct s_export	*next;
}	t_export;
#endif
