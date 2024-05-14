/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:20:42 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/14 16:13:18 by mamazari         ###   ########.fr       */
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
		if (ft_strncmp(str, buf[i], ft_strlen(buf[i])) == 0)
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

void	my_pwd(void)
{
	char	*buf;
	char	*res;

	buf = (char *) malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		exit(0);
	res = getcwd(buf, PATH_MAX);
	res[PATH_MAX] = '\0';
	if (res != NULL)
	{
		ft_putstr_fd(res, 1);
		free(res);
	}
	else
		exit(0);
}

void	my_echo(char **strs)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (ft_strncmp("-n", strs[i], 2) == 0)
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
	if (flag == 0)
		printf("\n");
}

int	contains(char *s1, char *s2)
{
	char	**split;
	int		i;
	int		ans;

	split = ft_split(s1, '\n');
	i = 0;
	ans = 0;
	while (split[i])
	{
		if (ft_strncmp(s2, split[i], ft_strlen(s2)) == 0)
		{
			ans = 1;
			break ;
		}
		i++;
	}
	return (ans);
}

char	*my_env(char *str, char **envp, char *s)
{
	int		i;
	char	*s2;
	i = 0;
	if (str == NULL)
	{
		while (envp[i])
		{
			s2 = ft_strjoin(str, envp[i]);
			free(str);
			str = ft_strjoin(s2, "\n");
			free(s2);
			i++;
		}
	}
	if (contains(str, s) == 0)
	{
		s2 = ft_strjoin(str, s);
		free(str);
		str = ft_strjoin(s2, "\n");
		free(s2);
	}
	return (str);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

void	populate(t_export **l, char **split)
{
	char		*env_val;
	int			len;
	t_export	*new;
	t_content	*cont;

	len = split_len(split);
	env_val = getenv(split[0]);
	cont = ft_content_new(split[0], env_val);
	new = (t_export *) ft_lstnew(cont);
	new->next = *l;
	*l = new;
}

t_export	*my_export(t_export *l, char **envp, char *s)
{
	int		i;
	char	*temp;
	char	**split;
	
	i = 0;
	if (l == NULL)
	{
		while (envp[i] != NULL)
		{
			split = ft_split(envp[i], '=');
			populate(&l, split);
			i++;
		}
		sort_list(&l);
	}
	split = ft_split(s, '=');
	if (ft_strlen(split[0]) >= 1 && is_inside(s, split[0], &l) == 0)
		append(s, split, &l);
	print_list(&l);
	return (l);
}

int	main2(int argc, char **argv, char **envp)
{
	t_export	*list = NULL;
	char	*str;
	
	while (1)
	{
		str = readline("minishell$ ");
		list = my_export(list, envp, str);
	}
	// ft_lstclear(&list, free);
	// system("leaks minishell");
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	main2(argc, argv, envp);
// 	// system("leaks minishell");
// 	return (0);
// }
