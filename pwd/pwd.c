/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:18:12 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/03 18:43:38 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "t_args.h"
#include "export/export.h"

char	*pwd(int i)
{
	char	*buf;
	char	*res;

	buf = (char *) malloc(sizeof(char) * 1025);
	res = getcwd(buf, 1024);
	res[1024] = '\0';
	if (i == 1)
	{
		ft_putstr_fd(res, 1);
		ft_putchar_fd('\n', 1);
	}
	return (res);
}

void	set_pwds(t_args *args)
{
	char	*path;
	char	*joined_str;

	path = pwd(0);
	export(args, "OLDPWD");
	joined_str = ft_strjoin("PWD=", path);
	free(path);
	export(args, joined_str);
	free(joined_str);
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
