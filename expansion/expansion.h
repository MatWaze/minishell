/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:12:50 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/30 16:45:04 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef struct s_export	t_export;

char	*expand(const char *str, t_export **evlist, int error);
int		expand_list(char **strs, t_export **evlist, int error);

#endif
