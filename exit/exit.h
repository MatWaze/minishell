/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:09:29 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/02 16:31:44 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

int				exit_no_arguments(char *num_str, t_args *args);
unsigned int	shell_exit(char **av, \
	unsigned int *exit_status, int p_count);
#endif
