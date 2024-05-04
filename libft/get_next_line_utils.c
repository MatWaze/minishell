/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:36:29 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/01 15:10:24 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdlib.h>

size_t	ft_strlen_gnl(const char *s, size_t max, int ignore_nl);

size_t	ft_strjoin1(char **s1, size_t res_len, char *s2, size_t len)
{
	size_t	joined_len;
	char	*tmp;
	size_t	i;

	joined_len = ft_strlen_gnl(s2, len, 0);
	tmp = (char *)malloc(res_len + joined_len + 1);
	if (tmp)
	{
		i = res_len;
		while (i--)
			tmp[i] = (*s1)[i];
		i = joined_len;
		while (i--)
			tmp[res_len + i] = s2[i];
		tmp[res_len + joined_len] = '\0';
		free(*s1);
		*s1 = tmp;
	}
	else
	{
		free(*s1);
		*s1 = NULL;
		s2[0] = '\0';
	}
	return (joined_len);
}

size_t	ft_strlen_gnl(const char *s, size_t max, int ignore_nl)
{
	size_t	result;

	result = 0;
	if (s)
	{
		while (max-- && *s)
		{
			if (!ignore_nl && *s == '\n')
				max = 0;
			else
				s++;
			result++;
		}
	}
	return (result);
}

void	ft_shift(char *buff, size_t pos, size_t len)
{
	size_t	i;

	i = 0;
	if (pos)
	{
		while (i < len)
		{
			buff[i] = buff[pos + i];
			i++;
		}
	}
	buff[len] = '\0';
}
