/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_heredoc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:10:43 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/25 07:57:15 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HEREDOC_H
# define T_HEREDOC_H
# include "t_hdlst.h"

typedef struct s_heredoc
{
	t_hdlst	*hdlst;
	int		fd;
}	t_heredoc;
#endif
