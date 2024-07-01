/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:53:43 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/21 16:08:44 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "t_args.h"

int			pipex(t_args *args);
void		kill_processes(t_list *pids);
void		get_exit_status(t_list *pids);

#endif