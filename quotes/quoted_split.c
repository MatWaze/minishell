/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin < zanikin@student.42yerevan.am>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:17:38 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/12 09:58:16 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

static char	*ft_strndup(char *src, int n);
static int	count_strings(char *str, char *set);
static int	ft_split_loop(char *str, char *set, char **output);
static void	free_split_output(char **output);
char		track_quote(const char *str, char assumed_qtype, int stop);

char	**quoted_split(char *str, char *set)
{
	char	**output;
	int		count;

	output = NULL;
	if (str)
	{
		count = count_strings(str, set);
		output = (char **)malloc(sizeof(char *) * (count + 1));
		if (output && ft_split_loop(str, set, output))
		{
			free_split_output(output);
			output = NULL;
		}
	}
	return (output);
}

static void	free_split_output(char **output)
{
	size_t	i;

	i = 0;
	while (output[i])
		free(output[i++]);
	free(output);
}

static char	*ft_strndup(char *src, int n)
{
	char	*ret;
	char	*p;

	ret = (char *)malloc(sizeof(char) * (n + 1));
	p = ret;
	if (p)
	{
		while (n)
		{
			*p++ = *src++;
			n--;
		}
		*p = 0;
	}
	return (ret);
}

static int	count_strings(char *str, char *set)
{
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	track_quote(str, '\0', 0);
	while (str[i])
	{
		if (track_quote(NULL, '\0', 0) || ft_strchr(set, str[i]) == NULL)
		{
			count++;
			j = i + 1;
			while (str[j] && (track_quote(NULL, '\0', 1)
					|| ft_strchr(set, str[j]) == NULL))
			{
				j++;
				track_quote(NULL, '\0', 0);
			}
			i = j - 1;
		}
		i++;
	}
	return (count);
}

static int	ft_split_loop(char *str, char *set, char **output)
{
	int	j;
	int	i;
	int	count;
	int	error;

	i = 0;
	j = 0;
	error = 0;
	track_quote(str, '\0');
	while (!error && str[i])
	{
		if (track_quote(NULL, '\0') || ft_strchr(set, str[i]) == NULL)
		{
			count = 1;
			while (str[i + count] && (track_quote(NULL, '\0')
					|| ft_strchr(set, str[i + count]) == NULL))
				count++;
			output[j] = ft_strndup(str + i, count);
			error = output[j++] == NULL;
			i += count - 1;
		}
		i++;
	}
	output[j] = NULL;
	return (error);
}
