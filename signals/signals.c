/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:12:13 by mamazari          #+#    #+#             */
/*   Updated: 2024/07/01 21:23:01 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

#include "libft/libft.h"

extern int	g_exit_status;

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

void	remove_echo_ctl(void)
{
	struct termios	t;

	if (tcgetattr(0, &t) == 0)
	{
		t.c_lflag &= ~(ECHOCTL);
		tcsetattr(0, TCSANOW, &t);
	}
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
