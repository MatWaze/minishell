/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/16 13:12:19 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

void	setup_fds(t_temp *p) 
{
	p->tempin = dup(0);
	p->tempout = dup(1);
	p->fdin = dup(p->tempin);
}

void	restore_fds(t_temp *p) 
{
	dup2(p->tempin, 0);
	dup2(p->tempout, 1);
	close(p->tempin);
	close(p->tempout);
}

int	handle_builtin(char **av, t_args *args) 
{
	int	i;
	int	ans;

	i = 0;
	ans = 0;
	if (ft_strncmp("export", av[0], 6) == 0) 
	{
		while (av[i])
			args->list = my_export(args->list, args->envp, av[i++]);
		print_list(&args->list);
	}
	return (ans);
}

void	handle_command(char **av, t_args *args) 
{
	int		p;
	char	*command;

	p = fork();
	if (p == 0) 
	{
		command = search_path(av[0], args->envp);
		execve(command, av, args->envp);
		perror(av[0]);
		exit(errno);
	}
}

int	handle_pipe(int j, t_args *args, t_temp *p) 
{
	char	**av;
	int		ans;
	
	ans = 0;
	dup2(p->fdin, 0);
	close(p->fdin);
	av = ft_split(args->argv[j], ' ');
	if (j == args->p_count)
		p->fdout = dup(p->tempout);
	else 
	{
		p->fd = (int *) malloc(sizeof(int) * 2);
		pipe(p->fd);
		p->fdout = p->fd[1];
		p->fdin = p->fd[0];
	}
	dup2(p->fdout, 1);
	close(p->fdout);
	if (is_builtin(av[0]) == 1)
		ans = handle_builtin(av, args);
	else
		handle_command(av, args);
	return (ans);
}

int	pipex(t_args *args) 
{
	t_temp	p;
	int		j;
	int		exit_status;
	int		status;
	int		ans;
	
	exit_status = 0;
	setup_fds(&p);
	j = 0;
	while (j < args->p_count + 1)
		ans = handle_pipe(j++, args, &p);
	restore_fds(&p);
	if (ans == 0)
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_args	args;
// 	int		*fd;
// 	int		i;
// 	int		j;

// 	args.argc = argc;
// 	args.argv = argv;
// 	args.envp = envp;
// 	fd = (int *) malloc(sizeof(int) * ((argc - 1) * 2 - 2));
// 	j = 0;
// 	i = 0;
// 	while (i < (argc - 1) * 2 - 2)
// 	{
// 		pipe(fd + j);
// 		j += 2;
// 		i++;
// 	}
// 	pipex(args, fd);
// 	close_all(fd, argc);
// 	free(fd);
// 	leave_children();
// 	return (0);
// }
