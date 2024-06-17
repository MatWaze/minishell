/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:08:16 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/17 14:15:56 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

void	free_arr(char **av);
void	print_error_msg(char *msg, char *cmd);
int		ft_str_is_numeric(char *str);
int		ft_str_is_alpha(char *str);

#endif
