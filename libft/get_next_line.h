/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:10:50 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/01 15:10:26 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50ul
# endif
# include <sys/types.h>

size_t	ft_strjoin1(char **s1, size_t res_len, char *s2, size_t len);
size_t	ft_strlen_gnl(const char *s, size_t max, int ignore_nl);
void	ft_shift(char *buff, size_t pos, size_t len);

#endif
