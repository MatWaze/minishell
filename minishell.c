/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/05 13:22:27 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// prompt; history; run executables; redirections; ' and ";
// pipes; env vars; $? ; ctrl-C; ctrl-D; ctrl-\; built-ins

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "quotes/quotes.h"
#include "pwd/pwd.h"
#include "export/export.h"
#include "pipex/pipex.h"
#include "common/common.h"

static void	run_pipex(t_args *args, char **words, char *str);
static void	init_minishell(char **envp, t_args *args);

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
		if (*str != 0)
		{
			words = quoted_split(str, '|');
			run_pipex(&args, words, str);
		}
		free(str);
	}
	ft_lstclear((t_list **)&args.export_list, free_export_content);
	ft_lstclear((t_list **)&args.env_list, free_export_content);
	ft_lstclear(&args.pids, free);
	free(args.pids);
	return (args.exit_code);
}

static void	init_minishell(char **envp, t_args *args)
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

static void	run_pipex(t_args *args, char **words, char *str)
{
	int		i;
	t_list	*list;

	i = 0;
	args->p_count = 0;
	args->argv = words;
	while (str[i])
	{
		if (str[i] == '|' && !quotes_type(str, str + i))
			args->p_count++;
		i++;
	}
	pipex(args);
	list = args->pids;
	while (list)
	{
		waitpid(*(int *) list->content, &args->exit_code, 0);
		list = list->next;
	}
	args->exit_code = WEXITSTATUS(args->exit_code);
	free_arr(args->argv);
	ft_lstclear(&args->pids, free);
}
