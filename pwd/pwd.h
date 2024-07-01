/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:15:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/03 18:39:52 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PWD_H
# define PWD_H
# include "t_args.h"

char	*pwd(int i);
void	set_pwds(t_args *args);
void	update_pwd(t_args *args, char *prev_pwd, char *cur_pwd);
#endif
