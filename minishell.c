/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:29 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/16 13:13:21 by mamazari         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_export	*l;
	t_args		*args;
	char		*str;
	char		*crin;
	char		**split;
	char		**words1;
	int			i;
	int			p_count;
	int			*fd;
	int			exit_status;
	
	args = (t_args *) malloc(sizeof(t_args));
	args->envp = envp;
	i = 0;
	l = NULL;
	while (args->envp[i] != NULL)
	{
		split = ft_split(args->envp[i], '=');
		populate(&l, split);
		i++;
	}
	sort_list(&l);
	args->list = l;
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