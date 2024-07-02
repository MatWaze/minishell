/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/07/02 21:42:06 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

#include "quotes/quotes.h"
#include "pwd/pwd.h"
#include "export/export.h"
#include "pipex/pipex.h"
#include "common/common.h"
#include "redirection/redirection.h"
#include "signals/signals.h"

int	g_exit_status = 0;

static void	run_pipex(t_args *args, char **words, char *str);
static void	set_size(size_t *size, char *str);
static void	init_minishell(char **envp, t_args *args);
static int	main_loop(t_args *args);

int	main(int argc, char **argv, char **envp)
{
	t_args				args;
	int					running;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell doesn't take any arguments.\n", 2);
		exit(1);
	}
	remove_echo_ctl();
	init_minishell(envp, &args);
	running = 1;
	while (running)
		running = main_loop(&args);
	ft_lstclear((t_list **)&args.export_list, free_export_content);
	ft_lstclear((t_list **)&args.env_list, free_export_content);
	ft_lstclear(&args.pids, free);
	free(args.pids);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	return (g_exit_status);
}

static void	init_minishell(char **envp, t_args *args)
{
	t_export	*export_list;
	t_export	*env_list;
	char		**split;
	int			i;

	i = 0;
	args->p_count = 0;
	args->quotes_closed = 0;
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
	sort_list(&export_list);
	set_pwds(args);
}

static int	main_loop(t_args *args)
{
	char		*str;
	size_t		size;
	static char	qstr[2] = {0};

	init_signals(0);
	str = readline("minishell$ ");
	init_signals(1);
	set_size(&size, str);
	if (size)
	{
		add_history(str);
		args->quotes_closed = quotes_type(str, str + size);
		if (args->quotes_closed)
		{
			qstr[0] = args->quotes_closed;
			print_error_msg("unclosed quote", (char *)qstr);
			g_exit_status = 1;
		}
		else
			run_pipex(args, quoted_split(str, "|"), str);
	}
	free(str);
	return (str != NULL);
}

static void	set_size(size_t *size, char *str)
{
	if (str)
		*size = ft_strlen(str);
	else
		*size = 0;
}

static void	run_pipex(t_args *args, char **words, char *str)
{
	int	i;
	int	error;

	i = 0;
	args->p_count = 0;
	args->argv = words;
	while (str[i])
	{
		if (str[i] == '|' && !quotes_type(str, str + i))
			args->p_count++;
		i++;
	}
	args->hd_count = count_heredoc((const char **)words);
	error = pipex(args, 0);
	g_exit_status = error != 0;
	if (error == 1)
	{
		print_error_msg("failed: Resource temporarily unavailable", "fork");
		kill_processes(args->pids);
	}
	else if (error == 0)
		get_exit_status(args->pids);
	free_arr(args->argv);
	ft_lstclear(&args->pids, free);
}
