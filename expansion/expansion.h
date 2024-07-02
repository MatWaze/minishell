/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:12:50 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 13:53:14 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "export/t_export.h"

char	*expand(const char *str, t_export **evlist, int error, int mask);
int		expand_list(char **strs, t_export **evlist, int error, int mask);
int		is_inside_quotes(char type, char *qtype);
#endif
