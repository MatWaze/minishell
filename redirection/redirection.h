/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:24:16 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/18 16:07:50 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H
# include "t_env_exp.h"
# include "t_fd.h"
# include "t_hdlst.h"

char	**remove_redirections(const char *str, t_fd *fds, t_hdlst **dels,
			t_env_exp	*env_exp);
void	heredoc(t_hdlst **pdels);
#endif
