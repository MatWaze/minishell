/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:17:38 by mamazari          #+#    #+#             */
/*   Updated: 2024/05/14 16:18:42 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	word_count(char *str, char *charset)
{
	int	i;
	int	word;
	int	count;

	i = 0;
	word = 0;
	count = 0;
	while (str[i])
	{
		if (!is_separator(str[i], charset) && word == 0)
		{
			count++;
			word = 1;
		}
		else if (is_separator(str[i], charset))
			word = 0;
		i++;
	}
	return (count);
}

int	len(char *str, char *charset)
{
	int	i;

	i = 0;
	while (!is_separator(str[i], charset) && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *dest, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) malloc(sizeof(1) * (len + 1));
	while (i < len)
	{
		str[i] = dest[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**my_split(char *str, char *charset)
{
	int		i;
	int		j;
	int		word;
	char	**ans;

	i = 0;
	j = 0;
	word = 0;
	ans = malloc(sizeof(char *) * (word_count(str, charset) + 1));
	while (str[i])
	{
		if (!is_separator(str[i], charset) && word == 0)
		{
			word = 1;
			ans[j] = ft_strdup(&str[i], len(&str[i], charset));
			j++;
		}
		else if (is_separator(str[i], charset))
			word = 0;
		i++;
	}
	ans[j] = NULL;
	return (ans);
}
