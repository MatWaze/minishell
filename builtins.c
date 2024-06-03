/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:20:42 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/03 19:23:41 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(char *msg, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
}

int	is_builtin(char *str)
{
	static char	*buf[8] = {"echo", "cd", "pwd", "export", \
		"unset", "env", "exit", NULL};
	int			i;
	int			ans;

	i = 0;
	ans = 0;
	while (buf[i] != NULL)
	{
		if (ft_strncmp(str, buf[i], ft_strlen(str)) == 0)
			ans = 1;
		i++;
	}
	return (ans);
}

int	check_key(char *key)
{
	int	ans;

	ans = 0;
	if (ft_isalpha(*key) == 1 || *key == '_')
		ans = 1;
	return (ans);
}
