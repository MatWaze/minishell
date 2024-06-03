/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:39:00 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/03 19:54:23 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H
# include "t_export.h"

int			find_key(t_export *export_list, char *key);
void		free_export_content(t_keyval *content);
void		print_list(t_export **list, int i);
t_keyval	*ft_content_new(char *key, char *val);
void		populate(t_export **l, char *key);
void		sort_list(t_export **l);
char		*get_value_from_key(t_export **list, char *key);
int			export(t_args *args, char *s);
#endif
