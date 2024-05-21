/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/20 20:35:37 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

// prompt; history; run executables; redirections; ' and ";
// pipes; env vars; $? ; ctrl-C; ctrl-D; ctrl-\; built-ins

int	pipe_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|')
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
	int		j;
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

int	main(int argc, char **argv, char **envp)
{
	t_export	*export_list;
	t_export	*env_list;
	t_args		*args;
	char		*str;
	char		*crin;
	char		**split;
	char		**words1;
	int			i;
	int			p_count;
	int			*fd;
	int			exit_status;
	t_list		*pids;
	
	args = (t_args *) malloc(sizeof(t_args));
	args->envp = envp;
	i = 0;
	export_list = NULL;
	env_list = NULL;
	pids = NULL;
	args->pids = pids;
	while (envp[i] != NULL)
	{
		split = ft_split(envp[i], '=');
		populate(&export_list, split);
		populate(&env_list, split);
		i++;
	}
	args->envp = envp;
	args->env_list = env_list;
	sort_list(&export_list);
	args->export_list = export_list;
	// args->my_envp = change_envp(&args->env_list);
	while (1)
	{
		str = readline("minishell$ ");
		if (ft_strlen(str) > 0)
			add_history(str);
		if (*str != 0)
		{
			words1 = my_split(str, "|");
			args->argv = words1;
			args->exit_code = 0;
			p_count = pipe_count(str);
			args->p_count = p_count;
			exit_status = pipex(args);
			// printf("exit_status: %d\n", exit_status);
			leave_children();
			free_arr(words1);
		}
		free(str);
	}
}