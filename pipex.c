/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/04 17:42:57 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

void	pipex(t_args args, int fd[])
{
	int	i;
	int	j;
	int	p;

	do_execve_first(args, fd);
	j = 1;
	i = 0;
	while (j < args.p_count)
	{
		p = fork();
		if (p == 0)
			do_execve_fd(args, fd, &i, &j);
		j++;
		i += 2;
	}
	do_execve_last(args, fd, &i);
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
