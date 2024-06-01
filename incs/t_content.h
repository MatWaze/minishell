/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_content.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:10:05 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/01 10:17:19 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CONTENT_H
# define T_CONTENT_H

typedef struct s_content
{
	char				*val;
	char				*key;
	struct s_content	*next;
}	t_content;
#endif
