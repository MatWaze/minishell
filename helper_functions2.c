/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:13:06 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/11 16:23:17 by mamazari         ###   ########.fr       */
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

int	quotes_closed(char *str)
{
	t_list	*list;
	int		i;
	int		flag;
	int		flag2;
	
	i = 0;
	flag = 0;
	flag2 = 0;
	while (str[i])
	{
		// printf("char: [%c]\n", str[i]);
		if (str[i] == '\'' && flag == 0 && flag2 == 0)
			flag++;
		else if (str[i] == '\'' && flag != 0)
			flag--;
		if (str[i] == '\"' && flag2 == 0 && flag == 0)
			flag2++;
		else if (str[i] == '\"' && flag2 != 0)
			flag2--;
		// printf("flag: %d\nflag2: %d\n", flag, flag2);
		i++;
	}
	return (flag2 == 0 && flag == 0);
}

char	*get_command(char *str)
{
	int		count;
	char	*ans;
	int		i;
	
	if (quotes_closed(str) == 0)
		return (NULL);
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (!(str[i] == '\'' || str[i] == '\"'))
			count++;
	}
	ans = malloc(count + 1);
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (!(str[i] == '\'' || str[i] == '\"'))
			ans[count++] = str[i];
	}
	ans[count] = '\0';
	return (ans);
}

int	do_execve_first(t_args args, int fd[])
{
	char	**av;
	char	*command;
	int		exit_status;
	int		status;

	exit_status = 0;
	if (fork() == 0)
	{
		dup2(fd[1], 1);
		close_all(fd, args.p_count);
		av = ft_split(args.argv[0], ' ');
		if (av[0][0] == '/' || (av[0][0] == '.' && av[0][1] == '/'))
		{
			for (int i = 0; av[i]; i++)
				av[i] = get_command(av[i]);
			command = av[0];
			execve(command, av, args.envp);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			for (int i = 0; av[i]; i++)
				av[i] = get_command(av[i]);
			command = search_path(av[0], args.envp);
			execve(command, av, args.envp);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(127);
	}
	if (args.p_count == 0)
	{
		wait(&status);
		exit_status = WEXITSTATUS(status);
	}

	return (exit_status);
}

void	do_execve_fd(t_args args, int fd[], int *i, int *j)
{
	char	**av;
	char	*command;
	
	av = ft_split(args.argv[*j], ' ');
	dup2(fd[*i], 0);
	dup2(fd[*i + 3], 1);
	close_all(fd, args.p_count);
	if (av[0][0] == '/' || (av[0][0] == '.' && av[0][1] == '/'))
	{
		for (int i = 0; av[i]; i++)
			av[i] = get_command(av[i]);
		command = get_command(av[0]);
		execve(command, av, args.envp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		for (int i = 0; av[i]; i++)
			av[i] = get_command(av[i]);
		command = search_path(av[0], args.envp);
		execve(command, av, args.envp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(0);
}

int	do_execve_last(t_args args, int fd[], int *i)
{
	char	**av;
	char	*command;
	int		p;
	int		exit_status;
	int		status;
	int		ret;
	
	exit_status = 0;
	ret = 0;
	p = fork();
	if (p == 0)
	{
		dup2(fd[*i], 0);
		close_all(fd, args.p_count);
		av = ft_split(args.argv[args.p_count], ' ');
		if (av[0][0] == '/' || (av[0][0] == '.' && av[0][1] == '/'))
		{
			for (int i = 0; av[i]; i++)
				av[i] = get_command(av[i]);
			command = av[0];
			for (int i = 0; av[i]; i++)
				av[i] = get_command(av[i]);
			ret = execve(command, av, args.envp);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
		else
		{
			for (int i = 0; av[i]; i++)
				av[i] = get_command(av[i]);
			command = search_path(av[0], args.envp);
			ret = execve(command, av, args.envp);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(1);
		}
	}
	wait(&status);
	exit_status = WEXITSTATUS(status);
	return (exit_status);
}

// int	main(int argc, char **argv)
// {
// 	char	*str;
	
// 	if (get_command(str) == 1)
// 		printf("%s is correct\n", str);
// 	else
// 		printf("%s is incorrect\n", str);
// }