/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin < zanikin@student.42yerevan.am>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/10 19:37:37 by zanikin          ###   ########.fr       */
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
static int	main_loop(t_args *args);

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	int		running;

	(void)argc;
	(void)argv;
	init_minishell(envp, &args);
	running = 1;
	while (running)
	{
		running = main_loop(&args);
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

static int	main_loop(t_args *args)
{
	char	*str;
	size_t	size;
	char	qstr[2];

	str = readline("minishell$ ");
	if (str)
		size = ft_strlen(str);
	else
		size = 0;
	if (size)
	{
		add_history(str);
		args->exit_code = quotes_type(str, str + size);
		if (args->exit_code)
		{
			qstr[0] = (char)args->exit_code;
			qstr[1] = '\0';
			print_error_msg("Unclosed quote\n", (char *)qstr);
			args->exit_code = 1;
		}
		else
			run_pipex(args, quoted_split(str, "|"), str);
	}
	free(str);
	return (str != NULL);
}

static void	run_pipex(t_args *args, char **words, char *str)
{
	int		i;

	args->p_count = 0;
	i = 0;
	args->argv = words;
	while (str[i])
	{
		if (str[i] == '|' && !quotes_type(str, str + i))
			args->p_count++;
		i++;
	}
	if (pipex(args) == 1)
	{
		print_error_msg("failed: Resource temporarily unavailable\n", \
			"fork");
		kill_processes(args->pids);
		args->exit_code = 1;
	}
	else
		get_exit_status(args);
	free_arr(args->argv);
	ft_lstclear(&args->pids, free);
}
