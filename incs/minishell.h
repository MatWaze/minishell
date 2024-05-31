/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:44:22 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/29 20:19:10 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "readline/history.h"
# include "readline/readline.h"
# include "libft.h"
# include <dirent.h>
#include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include "builtins.h"
// # include <check.h>

char	**quoted_split(char *str, char c);
char	*search_path(char *cmd, t_export **env);
char	*get_str(char **strs2, char *cmd);
void	free_arr(char **av);
void	leave_children(void);
void	init_minishell(char **envp, t_args *args);
void	set_params(t_args *args, char **words, char *str);
void	close_all(int fd[], int argc);
void	pipex(t_args *args);
char	quotes_type(const char *str, const char *const pc);

#endif
