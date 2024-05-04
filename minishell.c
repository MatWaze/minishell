/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/04 15:45:29 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

// prompt; history; run executables; redirections; ' and ";
// pipes; env vars; $? ; ctrl-C; ctrl-D; ctrl-\; built-ins

int	is_builtin(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 0;
	char	*buf[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	while (buf[i] != NULL)
	{
		if (ft_strncmp(str, buf[i], ft_strlen(buf[i])) == 0)
			ans = 1;
		i++;
	}
	return (ans);
}

int	is_cmd(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 0;
	if (access(str, F_OK | R_OK) == 0 || is_builtin(str) == 1)
		ans = 1;
	return (ans);
}

void	do_execve_red(char *strs, char **envp, int file)
{
	char	**av;
	char	*command;

	if (fork() == 0)
	{
		av = ft_split(strs, ' ');
		command = search_path(av[0], envp);
		dup2(file, 1);
		if (execve(command, av, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}

void	do_execve(char *command, char **splitted, char **envp)
{
	if (fork() == 0)
	{
		if (execve(command, splitted, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}

int	create_fd(char *name)
{
	int	fd;

	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (fd);
}
int	pipe_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|')
			c++;
		i++;
	}
	return (c);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**words1;
	char	*command;
	char	**splitted;
	int		j;
	int		p_count;
	
	
	while (1)
	{
		str = readline("minishell$ ");
		if (ft_strlen(str) > 0)
			add_history(str);
		j = 0;
		words1 = my_split(str, "|");
		p_count = pipe_count(str);
	}
}