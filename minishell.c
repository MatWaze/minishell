/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/03 18:19:10 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prompt; history; run executables; redirections; ' and ";
// pipes; env vars; $? ; ctrl-C; ctrl-D; ctrl-\; built-ins

int	pipe_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|' && !quotes_type(str, str + i))
			c++;
		i++;
	}
	return (c);
}

void	init_minishell(char **envp, t_args *args)
{
	t_export	*export_list;
	t_export	*env_list;
	char		**split;
	int			i;

	i = 0;
	args->envp = envp;
	export_list = NULL;
	env_list = NULL;
	while (envp[i] != NULL)
	{
		split = ft_split(envp[i], '=');
		populate(&export_list, split[0]);
		populate(&env_list, split[0]);
		free_arr(split);
		i++;
	}
	args->env_list = env_list;
	args->export_list = export_list;
	args->pids = NULL;
	args->exit_code = 0;
	sort_list(&export_list);
	set_pwds(args);
}

int	wait_for_children(t_args *args)
{
	pid_t	pid;
	t_list	*list;

	list = args->pids;
	while (list)
	{
		pid = *(int *) list->content;
		waitpid(pid, &args->exit_code, 0);
		list = list->next;
	}
	return (args->exit_code);
}

void	run_pipex(t_args *args, char **words, char *str)
{
	int	p_count;
	int	status;

	args->argv = words;
	p_count = pipe_count(str);
	args->p_count = p_count;
	pipex(args);
	status = wait_for_children(args);
	args->exit_code = WEXITSTATUS(status);
	free_arr(args->argv);
	ft_lstclear(&args->pids, free);
}

void	free_lists(t_args *args)
{
	ft_lstclear((t_list **)&args->export_list, free_export_content);
	ft_lstclear((t_list **)&args->env_list, free_export_content);
	ft_lstclear(&args->pids, free);
}

int	main(int argc, char **argv, char **envp)
{
	t_args		args;
	char		*str;
	char		**words;

	(void)argc;
	(void)argv;
	init_minishell(envp, &args);
	while (1)
	{
		str = readline("minishell$ ");
		if (ft_strlen(str) > 0)
			add_history(str);
		if (*str == 'y' && ft_strlen(str) == 1)
			break ;
		if (*str != 0)
		{
			words = quoted_split(str, '|');
			run_pipex(&args, words, str);
		}
		free(str);
	}
	free_lists(&args);
	free(args.pids);
	return (args.exit_code);
}
