/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:46:35 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/03 19:53:59 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	print_error_msg(char *msg, char *cmd);

int	cd(char *path)
{
	int		ans;

	ans = 0;
	if (!path || chdir(path) == -1)
	{
		if (!path)
			print_error_msg("HOME is not set\n", "cd");
		else
			perror(path);
		ans = 1;
	}
	return (ans);
}
