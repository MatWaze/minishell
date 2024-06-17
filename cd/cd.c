/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:46:35 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/17 14:11:31 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "common/common.h"

int	cd(char *path)
{
	int		ans;

	ans = 0;
	if (!path || chdir(path) == -1)
	{
		if (!path)
			print_error_msg("HOME is not set", "cd");
		else
			perror(path);
		ans = 1;
	}
	return (ans);
}
