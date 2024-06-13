/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hdlst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin < zanikin@student.42yerevan.am>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:20:19 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/10 09:24:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HDLST_H
# define T_HDLST_H

typedef struct s_hdlst
{
	char			*str;
	struct s_hdlst	*next;
}	t_hdlst;
#endif
