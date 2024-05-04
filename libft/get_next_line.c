/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:35:09 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/01 15:10:33 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static char		*get_line(int fd, char *buff, ssize_t *count);
static size_t	join(char **result, char *buff, size_t *size, ssize_t *count);
static size_t	get_buffer(char **buff);

char	*get_next_line(int fd)
{
	static char	*buffers[OPEN_MAX] = {NULL};
	ssize_t		count;
	char		*result;

	result = NULL;
	if (fd >= 0 && fd < OPEN_MAX)
	{
		count = get_buffer(buffers + fd);
		if (buffers[fd])
			result = get_line(fd, buffers[fd], &count);
		if (count == -1)
		{
			free(result);
			result = NULL;
			buffers[fd][0] = '\0';
		}
		if (buffers[fd] && buffers[fd][0] == '\0')
		{
			free(buffers[fd]);
			buffers[fd] = NULL;
		}
	}
	return (result);
}

static size_t	get_buffer(char **buff)
{
	size_t	count;

	if (*buff)
		count = ft_strlen_gnl(*buff, BUFFER_SIZE, 1);
	else
	{
		count = 0;
		*buff = (char *)malloc(BUFFER_SIZE);
		if (*buff)
			**buff = '\0';
	}
	return (count);
}

static char	*get_line(int fd, char *buff, ssize_t *count)
{
	size_t	joined_len;
	ssize_t	tmp_count;
	char	*result;
	size_t	size;

	result = NULL;
	size = 0;
	joined_len = 1;
	while ((result == NULL || result[size - 1] != '\n') && joined_len)
	{
		if (*count == 0)
		{
			tmp_count = read(fd, buff, BUFFER_SIZE);
			if (tmp_count != -1)
				*count += tmp_count;
			else
				*count = -1;
		}
		joined_len = join(&result, buff, &size, count);
	}
	return (result);
}

static size_t	join(char **result, char *buff, size_t *size, ssize_t *count)
{
	size_t	joined_len;

	joined_len = 0;
	if (*count > 0)
	{
		joined_len = ft_strjoin1(result, *size, buff, *count);
		*size += joined_len;
		ft_shift(buff, joined_len, *count - joined_len);
		*count -= joined_len;
	}
	return (joined_len);
}
