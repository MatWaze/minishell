/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:13:06 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/05 15:05:26 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

char	**get_path(char **path)
{
	char	**strs1;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		strs1 = ft_split(path[i], '=');
		if (ft_strncmp(strs1[0], "PATH", 4) == 0)
			return (strs1);
		free_arr(strs1);
		i++;
	}
	return (NULL);
}

char	*search_path(char *cmd, char **path)
{
	char	**strs1;
	char	**strs2;

	strs1 = get_path(path);
	if (!strs1)
		return (NULL);
	cmd = ft_strjoin("/", cmd);
	strs2 = ft_split(strs1[1], ':');
	free_arr(strs1);
	return (get_str(strs2, cmd));
}

void	leave_children(void)
{
	int	i;
	int	status;

	i = wait(&status);
	while (i != -1)
		i = wait(&status);
}
void	close_all(int fd[], int argc)
{
	int	i;

	i = 0;
	while (i < argc * 2)
	{
		close(fd[i]);
		i++;
	}
}

void	do_execve_first(t_args args, int fd[])
{
	char	**av;
	char	*command;

	if (fork() == 0)
	{
		av = ft_split(args.argv[0], ' ');
		command = search_path(av[0], args.envp);
		dup2(fd[1], 1);
		close_all(fd, args.p_count);
		if (execve(command, av, args.envp) == -1)
		{
			perror(command);
			exit(0);
		}
	}
}

void	do_execve_fd(t_args args, int fd[], int *i, int *j)
{
	char	**av;
	char	*command;

	av = ft_split(args.argv[*j], ' ');
	command = search_path(av[0], args.envp);
	dup2(fd[*i], 0);
	dup2(fd[*i + 3], 1);
	close_all(fd, args.p_count);
	if (execve(command, av, args.envp) == -1)
	{
		perror(command);
		exit(0);
	}
}

void	do_execve_last(t_args args, int fd[], int *i)
{
	char	**av;
	char	*command;
	int		p;

	p = fork();
	if (p == 0)
	{
		av = ft_split(args.argv[args.p_count], ' ');
		command = search_path(av[0], args.envp);
		dup2(fd[*i], 0);
		close_all(fd, args.p_count);
		if (execve(command, av, args.envp) == -1)
		{
			perror(command);
			exit(0);
		}
	}
	else if (p == -1)
	{
		perror("fork");
		exit(0);
	}
}
