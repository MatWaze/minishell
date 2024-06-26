/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/26 17:19:04 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>

#include "quotes/quotes.h"
#include "pwd/pwd.h"
#include "export/export.h"
#include "pipex/pipex.h"
#include "common/common.h"

int	g_exit_status = 0;

static void	run_pipex(t_args *args, char **words, char *str);
static void	init_minishell(char **envp, t_args *args);
static int	main_loop(t_args *args);
static void	sigact_handler(int signum, siginfo_t *info, void *context);
static void	sigact_handler2(int signum, siginfo_t *info, void *context);

void	init_signals(int i)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (i == 0)
		sa.sa_sigaction = sigact_handler;
	else
		sa.sa_sigaction = sigact_handler2;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	disable_echoctl(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) != 0)
		return ;
	t.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int	main2(int argc, char **argv, char **envp)
{
	t_args				args;
	int					running;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell doesn't take any arguments.\n", 2);
		exit(1);
	}
	disable_echoctl();
	init_minishell(envp, &args);
	running = 1;
	while (running)
		running = main_loop(&args);
	ft_lstclear((t_list **)&args.export_list, free_export_content);
	ft_lstclear((t_list **)&args.env_list, free_export_content);
	ft_lstclear(&args.pids, free);
	free(args.pids);
	rl_clear_history();
	return (g_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	main2(argc, argv, envp);
	system("leaks minishell");
	return (0);
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

static void	sigact_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigact_handler2(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT || signum == SIGQUIT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

static int	main_loop(t_args *args)
{
	char				*str;
	size_t				size;
	char				qstr[2];

	init_signals(0);
	str = readline("minishell$ ");
	init_signals(1);
	if (str)
		size = ft_strlen(str);
	else
		size = 0;
	if (size)
	{
		add_history(str);
		args->quotes_closed = quotes_type(str, str + size);
		if (args->quotes_closed)
		{
			qstr[0] = (char)g_exit_status;
			qstr[1] = '\0';
			print_error_msg("Unclosed quote", (char *)qstr);
			g_exit_status = 1;
		}
		else
			run_pipex(args, quoted_split(str, '|'), str);
	}
	free(str);
	return (str != NULL);
}

static void	run_pipex(t_args *args, char **words, char *str)
{
	int		i;

	i = 0;
	args->p_count = 0;
	args->argv = words;
	while (str[i])
	{
		if (str[i] == '|' && !quotes_type(str, str + i))
			args->p_count++;
		i++;
	}
	if (pipex(args) == 1)
	{
		print_error_msg("failed: Resource temporarily unavailable", "fork");
		kill_processes(args->pids);
		g_exit_status = 1;
	}
	else
		get_exit_status(args->pids);
	free_arr(args->argv);
	ft_lstclear(&args->pids, free);
}
