/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:20:42 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/20 16:42:37 by mamazari         ###   ########.fr       */
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
	int	i;
	int	ans;

	i = 0;
	ans = 0;
	if (access(str, F_OK | R_OK) == 0 || is_builtin(str) == 1)
		ans = 1;
	return (ans);
}

int	my_cd(char *path, t_export **list)
{
	int	ans;

	ans = 0;
	if (ft_strlen(path) == 4 && ft_strncmp(path, "HOME", 4) == 0)
		path = get_value_from_key(list, "HOME");
	if (!path)
	{
		printf("minishell: HOME not set\n");
		ans = 1;
	}
	else if (chdir(path) == -1)
	{
		perror(path);
		ans = 1;
	}
	return (ans);
}

void	my_pwd(void)
{
	char	*buf;
	char	*res;

	buf = (char *) malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		exit(0);
	res = getcwd(buf, PATH_MAX);
	if (res != NULL)
	{
		res[PATH_MAX] = '\0';
		ft_putstr_fd(res, 1);
		ft_putchar_fd('\n', 1);
		free(res);
	}
	else
		exit(0);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

void	my_echo(char **strs)
{
	int	i;
	int	flag;

	flag = 0;
	if (split_len(strs) > 1)
	{
		i = 1;
		if (ft_strncmp("-n", strs[i], ft_strlen(strs[i])) == 0)
		{
			flag = 1;
			i++;
		}
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

void	populate(t_export **l, char **split)
{
	char		*env_val;
	int			len;
	t_export	*new;
	t_content	*cont;
	t_export	*last;

	len = split_len(split);
	env_val = getenv(split[0]);
	cont = ft_content_new(split[0], env_val);
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
	int		exit_code;
	
	split = ft_split(s, '=');
	if (check_key(split[0]) == 1)
	{
		if (ft_strlen(split[0]) >= 1 && \
			(is_inside(s, split[0], &args->env_list) == 0 || \
			is_inside(s, split[0], &args->export_list) == 0))
		{
			append(s, split, &args->export_list);
			append(s, split, &args->env_list);
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
