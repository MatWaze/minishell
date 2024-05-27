/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:12:50 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/27 20:16:11 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

char	*expand(const char *str, t_export **evlist, int error);
char	**expand_list(const char **strs, t_export **evlist, int error);

#endif
