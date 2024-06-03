/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/03 17:29:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_pid(int p, t_args *args);

void	setup_fds(t_fd *p)
{
	p->tempin = dup(0);
	p->tempout = dup(1);
	p->fdin = dup(p->tempin);
}

void	restore_fds(t_fd *p)
{
	dup2(p->tempin, 0);
	dup2(p->tempout, 1);
	close(p->tempin);
	close(p->tempout);
}

int	handle_export(t_args *args, char **av)
{
	int	i;
	int	ans;

	i = 1;
	ans = 0;
	while (av[i])
		ans = my_export(args, av[i++]);
	if (i == 1)
		print_list(&args->export_list, 1);
	return (ans);
}

int	handle_unset(t_args *args, char **av)
{
	int	i;
	int	ans;

	i = 1;
	ans = 0;
	while (av[i])
	{
		if (check_key(av[i]) == 1 && args->p_count == 0)
		{
			my_unset(&args->export_list, av[i]);
			my_unset(&args->env_list, av[i]);
		}
		else
		{
			ans = 1;
			print_error_msg("not a valid identifier\n", av[i]);
		}
		i++;
	}
	return (ans);
}

int	find_key(t_export *export_list, char *key)
{
	t_export	*temp;
	int			ans;

	ans = 0;
	temp = export_list;
	while (temp)
	{
		if (key && ft_strncmp(temp->pair->key, key, ft_strlen(key)) == 0)
		{
			ans = 1;
			break ;
		}
		temp = temp->next;
	}
	return (ans);
}

void	update_pwd(t_args *args, char *prev_pwd, char *cur_pwd)
{
	char	*str2;

	if (find_key(args->export_list, "PWD") == 1)
	{
		str2 = ft_strjoin("PWD=", cur_pwd);
		my_export(args, str2);
		free(str2);
	}
	if (find_key(args->export_list, "OLDPWD") == 1)
	{
		str2 = ft_strjoin("OLDPWD=", prev_pwd);
		my_export(args, str2);
		free(str2);
	}
}

void	free_pwds(char *pwd, char *cur_pwd, char *prev_pwd)
{
	free(pwd);
	free(cur_pwd);
	free(prev_pwd);
}

int	handle_cd(t_args *args, char **av)
{
	int		ans;
	char	*str;
	char	*prev_pwd;
	char	*cur_pwd;
	char	*pwd;

	pwd = my_pwd(0);
	prev_pwd = my_strdup(pwd);
	free(pwd);
	if (!av[1])
		str = get_value_from_key(&args->export_list, "HOME");
	else
		str = av[1];
	ans = my_cd(str);
	if (args->p_count != 0)
		my_cd(prev_pwd);
	if (str && av[1] && ft_strncmp(av[1], str, ft_strlen(str)) != 0)
		free(str);
	pwd = my_pwd(0);
	cur_pwd = my_strdup(pwd);
	if (ans == 0)
		update_pwd(args, prev_pwd, cur_pwd);
	free_pwds(pwd, cur_pwd, prev_pwd);
	return (ans);
}

int	builtin_exit_code(int exit_code, t_args *args)
{
	int	pid;
	int	ans;

	ans = 0;
	pid = fork();
	if (pid == 0)
		exit(exit_code);
	else if (pid == -1)
		ans = 1;
	else
		append_pid(pid, args);
	return (ans);
}

void	handle_exit(char **av, t_args *args)
{
	my_exit(av[1], args);
}

int	handle_builtin(char **av, t_args *args)
{
	char	*pwd;
	int		ans;

	ans = 0;
	if (ft_strlen(av[0]) == 6 && ft_strncmp("export", av[0], 6) == 0)
		ans = handle_export(args, av);
	else if (ft_strlen(av[0]) == 3 && ft_strncmp("env", av[0], 3) == 0)
		print_list(&args->env_list, 0);
	else if (ft_strlen(av[0]) == 5 && ft_strncmp("unset", av[0], 5) == 0)
		ans = handle_unset(args, av);
	else if (ft_strlen(av[0]) == 4 && ft_strncmp("echo", av[0], 4) == 0)
	{
		my_echo(&av[0]);
	}
	else if (ft_strlen(av[0]) == 3 && ft_strncmp("pwd", av[0], 3) == 0)
	{
		pwd = my_pwd(1);
		free(pwd);
	}
	else if (ft_strlen(av[0]) == 2 && ft_strncmp("cd", av[0], 2) == 0)
		ans = handle_cd(args, av);
	else if (ft_strlen(av[0]) == 4 && ft_strncmp("exit", av[0], 4) == 0)
		handle_exit(av, args);
	return (builtin_exit_code(ans, args));
}

char	*get_value_from_key(t_export **list, char *key)
{
	t_export	*temp;
	char		*ans;

	temp = *list;
	ans = NULL;
	while (temp)
	{
		if (ft_strncmp(key, temp->pair->key, \
			ft_strlen(temp->pair->key)) == 0)
		{
			ans = temp->pair->val;
			break ;
		}
		temp = temp->next;
	}
	return (ans);
}

int	my_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}

char	*get_ans(char *str, char *ans, char *home_dir)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(home_dir);
	while (str[i])
	{
		if (str[i] == '~')
			j += my_strncpy(&ans[j], home_dir, len);
		else
			ans[j++] = str[i];
		i++;
	}
	ans[j] = '\0';
	return (ans);
}

int	is_dir(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1)
		return (0);
	return (((file_info.st_mode) & S_IFMT) == S_IFDIR);
}

int	ft_str_is_numeric(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
			{
				ans = 0;
				break ;
			}
			i++;
		}
	}
	return (ans);
}

void	dir_error(char *first)
{
	if (is_dir(first) != 0)
	{
		print_error_msg("is a directory\n", first);
		exit(126);
	}
}

void	execute_command(char *first, char **av, char **envp, t_args *args)
{
	char	*command;

	dir_error(first);
	command = search_path(first, &args->export_list);
	if (command == NULL || access(command, F_OK) != 0)
	{
		print_error_msg("command not found\n", first);
		exit(127);
	}
	if (access(command, X_OK) != 0)
	{
		print_error_msg("Permission denied\n", first);
		exit(126);
	}
	if (execve(command, av, envp) == -1)
		print_error_msg("error", first);
	exit(1);
}

void	append_pid(int p, t_args *args)
{
	int		*pid_copy;
	t_list	*new;
	t_list	*last;

	pid_copy = (int *)malloc(sizeof(int));
	*pid_copy = p;
	new = ft_lstnew(pid_copy);
	if (!args->pids)
		args->pids = new;
	else
	{
		last = args->pids;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	new->next = NULL;
}

void	handle_command(char **av, t_args *args)
{
	if (av[0][0] == '/' && access(av[0], F_OK) != 0)
	{
		print_error_msg("No such file or directory\n", av[0]);
		exit(127);
	}
	execute_command(av[0], av, args->envp, args);
}

int	run_command(t_args *args, t_fd *p, char **av)
{
	int		pid;
	int		ans;

	ans = 0;
	pid = fork();
	if (pid == 0)
	{
		close(p->fdin);
		close(p->fdout);
		handle_command(av, args);
	}
	else if (pid == -1)
		ans = 1;
	else if (pid > 0)
		append_pid(pid, args);
	return (ans);
}

int	handle_pipe(int j, t_args *args, t_fd *p)
{
	char	**av;
	int		ans;

	ans = 0;
	dup2(p->fdin, 0);
	close(p->fdin);
	av = quoted_split(args->argv[j], ' ');
	if (expand_list(av, &args->env_list, args->exit_code))
	{
		if (j == args->p_count)
			p->fdout = dup(p->tempout);
		else
		{
			pipe(p->fd);
			p->fdout = p->fd[1];
			p->fdin = p->fd[0];
		}
		dup2(p->fdout, 1);
		close(p->fdout);
		if (is_builtin(av[0]) == 1)
			ans = handle_builtin(av, args);
		else
			ans = run_command(args, p, av);
	}
	free_arr(av);
	return (ans);
}

int	pipex(t_args *args)
{
	t_fd	p;
	int		j;
	int		ans;

	setup_fds(&p);
	j = 0;
	ans = 0;
	while (j < args->p_count + 1)
	{
		if (handle_pipe(j++, args, &p) == 1)
		{
			print_error_msg("failed: Resource temporarily unavailable\n", "fork");
			ans = 1;
			break ;
		}
	}
	restore_fds(&p);
	return (ans);
}
