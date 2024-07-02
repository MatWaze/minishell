/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:53:43 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 21:41:55 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "t_args.h"

int			pipex(t_args *args, int ans);
void		kill_processes(t_list *pids);
void		get_exit_status(t_list *pids);

#endif
