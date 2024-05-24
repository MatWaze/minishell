/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:20:42 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/24 13:22:01 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

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

int	is_cmd(char *str)
{
	//int	i;
	int	ans;

	//i = 0;
	ans = 0;
	if (access(str, F_OK | R_OK) == 0 || is_builtin(str) == 1)
		ans = 1;
	return (ans);
}

int	my_cd(char *path, t_export **list)
{
	int		ans;
	//char	*str;
	//int		i;

	ans = 0;
	//i = 0;
	if (ft_strlen(path) == 4 && ft_strncmp(path, "HOME", 4) == 0)
		path = get_value_from_key(list, "HOME");
	if (!path)
	{
		// printf("minishell: HOME not set\n");
		ans = 1;
	}
	else if (chdir(path) == -1)
	{
		printf("path: %s\n", path);
		perror(path);
		ans = 1;
	}
	return (ans);
}

char	*my_pwd(void)
{
	char	*buf;
	char	*res;

	buf = (char *) malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		exit(0);
	res = getcwd(buf, PATH_MAX);
	if (res != NULL)
		res[PATH_MAX] = '\0';
	// else
		// exit(0);
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

void	my_echo(char **strs)
{
	int		i;
	int		flag;
	//char	*trimmed;

	flag = 0;
	i = 1;
	if (split_len(strs) > 1)
	{
		set_flag(strs, &i, &flag);
		while (strs[i] != NULL)
		{
			printf("%s", strs[i]);
			if (strs[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (flag == 0)
		printf("\n");
}

char	*my_strdup(char *dest)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) malloc(sizeof(1) * (ft_strlen(dest) + 1));
	while (dest[i])
	{
		str[i] = dest[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	populate(t_export **l, char **split)
{
	char		*key;
	char		*val;
	t_export	*new;
	t_content	*cont;
	t_export	*last;

	key = my_strdup(split[0]);
	val = my_strdup(getenv(key));
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

// int	remove_first(t_export **list, char *str)
// {
// 	t_export	*temp;
// 	int			count;
// 	int			ans;

// 	ans = 0;
// 	temp = *list;
// 	if (ft_strlen(temp->pair->key) == ft_strlen(str))
// 	{
// 		count = ft_strlen(str);
// 		if (ft_strncmp(str, temp->pair->key, count) == 0)
// 		{
// 			*list = temp->next;
// 			free(temp);
// 			ans = 1;
// 		}
// 	}
// 	return (ans);
// }

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
				free(temp);
				break ;
			}
		}
		prev = temp;
		temp = temp->next;
	}
}

int	my_export(t_args *args, char *s)
{
	char	**split;
	char	*key;
	char	*key2;
	char	*val;
	char	*val2;
	int		exit_code;

	split = ft_split(s, '=');
	key = my_strdup(split[0]);
	key2 = my_strdup(split[0]);
	val = get_val(s);
	val2 = get_val(s);
	free_arr(split);
	if (check_key(key) == 1)
	{
		if ((ft_strlen(key) >= 1 && is_inside(val2, key2, &args->env_list) \
			== 0) || is_inside(val, key, &args->export_list) == 0)
		{
			append(val, key, &args->export_list);
			append(val2, key2, &args->env_list);
		}
		else
		{
			free(key);
			// if (val)
			// 	free(val);
			free(key2);
			// if (val2)
			// 	free(val2);
		}
		exit_code = 0;
	}
	else
	{
		printf("minishell: export: `%s': not a valid identifier\n", s);
		exit_code = 1;
	}
	return (exit_code);
}

// int	main2(int argc, char **argv, char **envp)
// {
// 	t_export	*list = NULL;
// 	char	*str;

// 	while (1)
// 	{
// 		str = readline("minishell$ ");
// 		list = my_export(list, envp, str);
// 	}
// 	// ft_lstclear(&list, free);
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	main2(argc, argv, envp);
// 	// system("leaks minishell");
// 	return (0);
// }
