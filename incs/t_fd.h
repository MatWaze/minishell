/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:16:28 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/17 09:15:20 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FD_H
# define T_FD_H

typedef struct s_fd
{
	int	tempin;
	int	tempout;
	int	fdout;
	int	fdin;
	int	fd[2];
	int	rfd;
	int	wfd;
}	t_fd;
#endif
