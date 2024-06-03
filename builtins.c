/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:20:42 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/03 12:56:14 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

void	print_error_msg(char *msg, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
}

int	is_builtin(char *str)
{
	static char	*buf[8] = {"echo", "cd", "pwd", "export", \
		"unset", "env", "exit", NULL};
	int			i;
	int			ans;

	i = 0;
	ans = 0;
	while (buf[i] != NULL)
	{
		if (ft_strncmp(str, buf[i], ft_strlen(str)) == 0)
			ans = 1;
		i++;
	}
	return (ans);
}

int	my_cd(char *path)
{
	int		ans;

	ans = 0;
	if (!path || chdir(path) == -1)
	{
		if (!path)
			print_error_msg("HOME is not set\n", "cd");
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(path);
		}
		ans = 1;
	}
	return (ans);
}

char	*my_pwd(int i)
{
	char	*buf;
	char	*res;

	buf = (char *) malloc(sizeof(char) * 1025);
	res = getcwd(buf, 1024);
	res[1024] = '\0';
	if (i == 1)
	{
		ft_putstr_fd(res, 1);
		ft_putchar_fd('\n', 1);
	}
	return (res);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

void	set_flag(char **strs, int *i, int *flag)
{
	char	*trimmed;

	while (strs[*i] && strs[*i][0] == '-')
	{
		trimmed = ft_strtrim(strs[*i], "n");
		if (!(ft_strlen(trimmed) == 1 && ft_strncmp(trimmed, "-", 1) == 0))
		{
			free(trimmed);
			break ;
		}
		else
		{
			*flag = 1;
			free(trimmed);
		}
		(*i)++;
	}
}

int	my_echo(char **strs)
{
	int		flag;
	int		i;

	flag = 0;
	i = 1;
	if (split_len(strs) > 1)
	{
		set_flag(strs, &i, &flag);
		while (strs[i])
		{
			ft_putstr_fd(strs[i], 1);
			if (strs[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

char	*my_strdup(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	if (!src)
		return (NULL);
	dup = (char *) malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	populate(t_export **l, char *key)
{
	char		*val;
	t_export	*new;
	t_content	*cont;
	t_export	*last;

	val = getenv(key);
	cont = ft_content_new(key, val);
	new = (t_export *) ft_lstnew(cont);
	if (*l == NULL)
		*l = new;
	else
	{
		last = *l;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	new->next = NULL;
}

int	check_key(char *key)
{
	int	ans;

	ans = 0;
	if (ft_isalpha(*key) == 1 || *key == '_')
		ans = 1;
	return (ans);
}

void	free_content(t_export *l)
{
	free(l->pair->key);
	free(l->pair->val);
	free(l->pair);
	free(l);
}

int	exit_no_arguments(char *num_str, t_args *args)
{
	int	ans;

	ans = 0;
	if (!num_str && args->p_count == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (!num_str)
		ans = 1;
	return (ans);
}

void	my_exit(char *num_str, t_args *args)
{
	unsigned long long	unum;
	long long			num;
	unsigned int		exit_status;
	char				*joined;

	if (exit_no_arguments(num_str, args) == 0)
	{
		num = ft_atoi(num_str);
		unum = (unsigned long long) ft_atoi(num_str);
		if (*num_str != '-' && (ft_str_is_numeric(num_str) == 0 || \
			(ft_strlen(num_str) > 19 || unum > LONG_MAX)))
		{
			joined = ft_strjoin(num_str, ": numeric argument required\n");
			print_error_msg(joined, "exit");
			free(joined);
			exit_status = 255;
		}
		else if (num < 0)
			exit_status = unum % 256;
		else
			exit_status = num % 256;
		if (args->p_count == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(exit_status);
		}
	}
}

void	my_unset(t_export **l, char *str)
{
	t_export	*temp;
	t_export	*prev;
	int			count;

	prev = NULL;
	temp = *l;
	while (temp)
	{
		if (ft_strlen(str) == ft_strlen(temp->pair->key))
		{
			count = ft_strlen(temp->pair->key);
			if (ft_strncmp(str, temp->pair->key, count) == 0)
			{
				if (prev == NULL)
					*l = temp->next;
				else
					prev->next = temp->next;
				free_content(temp);
				break ;
			}
		}
		prev = temp;
		temp = temp->next;
	}
}

void	free_values(char *val, char *val2, char **split)
{
	free_arr(split);
	free(val);
	free(val2);
}

void	append_to_lists(char *val, char *val2, char *key, t_args *args)
{
	append(val, key, &args->export_list);
	append(val2, key, &args->env_list);
}

int	my_export(t_args *args, char *s)
{
	char	**split;
	char	*key;
	char	*val;
	char	*val2;
	int		ans;

	split = ft_split(s, '=');
	key = split[0];
	val = get_val(s);
	val2 = get_val(s);
	if (check_key(key) == 1)
	{
		if (args->p_count == 0 && ((ft_strlen(key) >= 1 && \
			is_inside(val2, key, &args->env_list) == 0) || \
			is_inside(val, key, &args->export_list) == 0))
			append_to_lists(val, val2, key, args);
		ans = 0;
	}
	else
	{
		print_error_msg("not a valid identifier\n", key);
		ans = 1;
	}
	free_values(val, val2, split);
	return (ans);
}
