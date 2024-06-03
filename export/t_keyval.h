/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_keyval.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:10:05 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/01 10:17:19 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_KEYVAL_H
# define T_KEYVAL_H

typedef struct s_keyval
{
	char			*val;
	char			*key;
	struct s_keyval	*next;
}	t_keyval;
#endif
