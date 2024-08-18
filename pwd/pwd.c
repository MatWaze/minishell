/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:18:12 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/18 13:21:51 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "export/export.h"

char	*pwd(int i)
{
	char	*buf;
	char	*res;

	res = NULL;
	buf = (char *) malloc(sizeof(char) * 1025);
	if (buf)
	{
		res = getcwd(buf, 1024);
		if (res)
		{
			res[1024] = '\0';
			if (i == 1)
			{
				ft_putstr_fd(res, 1);
				ft_putchar_fd('\n', 1);
			}
		}
		else
			free(buf);
	}
	return (res);
}

void	set_pwds(t_args *args)
{
	char	*path;
	char	*joined_str;

	path = pwd(0);
	export(args, "OLDPWD");
	if (path)
	{
		joined_str = ft_strjoin("PWD=", path);
		free(path);
		export(args, joined_str);
		free(joined_str);
	}
}

void	update_pwd(t_args *args, char *prev_pwd, char *cur_pwd)
{
	char	*str2;

	if (find_key(args->export_list, "PWD") == 1)
	{
		str2 = ft_strjoin("PWD=", cur_pwd);
		export(args, str2);
		free(str2);
	}
	if (find_key(args->export_list, "OLDPWD") == 1)
	{
		str2 = ft_strjoin("OLDPWD=", prev_pwd);
		export(args, str2);
		free(str2);
	}
}
