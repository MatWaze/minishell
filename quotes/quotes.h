/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:55:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/01 10:05:33 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

char	**quoted_split(char *str, char c);
char	quotes_type(const char *str, const char *const pc);
#endif