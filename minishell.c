/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/31 13:30:19 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prompt; history; run executables; redirections; ' and ";
// pipes; env vars; $? ; ctrl-C; ctrl-D; ctrl-\; built-ins

void	print_linked_list(t_list *l);

int	pipe_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|' && !quotes_type(str, str + i))
			c++;
		i++;
	}
	return (c);
}

char	*find_val(t_export *l, char *to_find)
{
	t_export	*temp;
	char		*ans;
	int			count;

	ans = NULL;
	temp = l;
	while (temp)
	{
		if (ft_strlen(temp->pair->key) > ft_strlen(to_find))
			count = ft_strlen(temp->pair->key);
		else
			count = ft_strlen(to_find);
		if (ft_strncmp(temp->pair->key, to_find, count) == 0)
		{
			ans = temp->pair->val;
			break ;
		}
		temp = temp->next;
	}
	return (ans);
}

char	*env_expansion(char *s, t_export *l)
{
	int		i;
	char	*ans;

	i = 0;
	ans = s;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (ft_isalpha(s[i + 1]) == 1 || s[i + 1] == '_')
			{
				ans = find_val(l, &s[i + 1]);
				break ;
			}
		}
		i++;
	}
	return (ans);
}

// char	**change_envp(t_export **env_list)
// {
// 	t_export	*temp;
// 	char		*str;
// 	char		*joined_str;
// 	char		**new_envp;
// 	int			len;

// 	len = ft_lstsize((t_list *) *env_list);
// 	printf("len: %d\n", len);
// 	new_envp = (char **) malloc(sizeof(char *) * (len + 1));
// 	len = 0;
// 	temp = *env_list;
// 	while (temp)
// 	{
// 		joined_str = ft_strjoin(temp->pair->key, "=");
// 		str = ft_strjoin(joined_str, temp->pair->val);
// 		free(joined_str);
// 		new_envp[len++] = str;
// 		temp = temp->next;
// 	}
// 	new_envp[len] = NULL;
// 	return (new_envp);
// }

void	set_pwds(t_args *args)
{
	char	*pwd;
	char	*joined_str;

	pwd = my_pwd(0);
	my_export(args, "OLDPWD");
	joined_str = ft_strjoin("PWD=", pwd);
	free(pwd);
	my_export(args, joined_str);
	free(joined_str);
}

void	init_minishell(char **envp, t_args *args)
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

void	clear_export(t_export **exp)
{
	t_export	*temp;
	t_export	*to_free;

	temp = *exp;
	while (temp)
	{
		to_free = temp;
		temp = temp->next;
		free(to_free->pair->key);
		free(to_free->pair->val);
		free(to_free->pair);
		free(to_free);
	}
	*exp = NULL;
}

void	clear_list(t_list **l)
{
	t_list	*temp;
	t_list	*to_free;

	temp = *l;
	while (temp)
	{
		to_free = temp;
		temp = temp->next;
		free(to_free->content);
		free(to_free);
	}
	*l = NULL;
}

int	wait_for_children(t_args *args)
{
	pid_t	pid;
	t_list	*list;

	list = args->pids;
	while (list)
	{
		pid = *(int *) list->content;
		waitpid(pid, &args->exit_code, 0);
		list = list->next;
	}
	return (args->exit_code);
}

void	run_pipex(t_args *args, char **words, char *str)
{
	int	p_count;
	int	status;

	args->exit_code = 0;
	args->argv = words;
	p_count = pipe_count(str);
	args->p_count = p_count;
	pipex(args);
	status = wait_for_children(args);
	args->exit_code = WEXITSTATUS(status);
	free_arr(args->argv);
	clear_list(&args->pids);
}

void	free_lists(t_args *args)
{
	clear_export(&args->export_list);
	clear_export(&args->env_list);
	clear_list(&args->pids);
}

void	print_linked_list(t_list *l)
{
	while (l)
	{
		printf("pid: %d\n", *(int *)(l->content));
		l = l->next;
	}
}

int	main2(int argc, char **argv, char **envp)
{
	t_args		args;
	char		*str;
	char		**words;

	(void)argc;
	(void)argv;
	init_minishell(envp, &args);
	while (1)
	{
		str = readline("minishell$ ");
		if (ft_strlen(str) > 0)
			add_history(str);
		if (*str == 'y' && ft_strlen(str) == 1)
			break ;
		if (*str != 0)
		{
			words = quoted_split(str, '|');
			run_pipex(&args, words, str);
		}
		free(str);
	}
	free(str);
	free_lists(&args);
	free(args.pids);
	return (args.exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	main2(argc, argv, envp);
	system("leaks minishell");
	return (0);
}
