/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:09:29 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/14 19:15:28 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

unsigned int	shell_exit(char *num_str, t_args *args, \
	unsigned int *exit_status);
int				exit_too_many_arguments(char **av, \
	int *exit_status);

#endif
