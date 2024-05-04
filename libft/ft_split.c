/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:02:14 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/31 20:52:00 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_strndup(char *src, int n);
static int	count_strings(char *str, char c);
static int	ft_split_loop(char *str, char c, char **output);
static void	free_split_output(char **output);

char	**ft_split(char *str, char c)
{
	char	**output;
	int		count;

	output = NULL;
	if (str)
	{
		count = count_strings(str, c);
		output = (char **)malloc(sizeof(char *) * (count + 1));
		if (output && ft_split_loop(str, c, output))
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

static int	count_strings(char *str, char c)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			j = i + 1;
			while (str[j] && str[j] != c)
				j++;
			i = j - 1;
		}
		i++;
	}
	return (count);
}

static int	ft_split_loop(char *str, char c, char **output)
{
	int	j;
	int	i;
	int	count;
	int	error;

	i = 0;
	j = 0;
	error = 0;
	while (!error && str[i])
	{
		if (str[i] != c)
		{
			count = 1;
			while (str[i + count] && str[i + count] != c)
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
