/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:52:18 by zanikin           #+#    #+#             */
/*   Updated: 2024/06/04 19:10:52 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "common/common.h"
#include "export/export.h"
#include "unset/unset.h"
#include "cd/cd.h"
#include "pwd/pwd.h"
#include "t_args.h"

int	handle_export(t_args *args, char **av)
{
	int	i;
	int	ans;

	i = 1;
	ans = 0;
	while (av[i])
		ans = export(args, av[i++]);
	if (i == 1)
		print_list(&args->export_list, 1);
	return (ans);
}

int	handle_unset(t_args *args, char **av)
{
	int	i;
	int	ans;

	i = 1;
	ans = 0;
	while (av[i])
	{
		if (ft_isalpha(av[i][0]) || av[i][0] == '_')
		{
			unset(&args->export_list, av[i]);
			unset(&args->env_list, av[i]);
		}
		else
		{
			ans = 1;
			print_error_msg("not a valid identifier\n", av[i]);
		}
		i++;
	}
	return (ans);
}

int	handle_cd(t_args *args, char **av)
{
	int		ans;
	char	*str;
	char	*prev_pwd;
	char	*cur_pwd;
	char	*path;

	path = pwd(0);
	prev_pwd = ft_strdup(path);
	free(path);
	if (!av[1])
		str = get_value_from_key(&args->export_list, "HOME");
	else
		str = av[1];
	ans = cd(str);
	if (str && av[1] && ft_strncmp(av[1], str, ft_strlen(str)) != 0)
		free(str);
	path = pwd(0);
	cur_pwd = ft_strdup(path);
	if (ans == 0)
		update_pwd(args, prev_pwd, cur_pwd);
	free(pwd);
	free(cur_pwd);
	free(prev_pwd);
	return (ans);
}
