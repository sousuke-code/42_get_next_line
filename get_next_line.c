/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyatasoujo <miyatasoujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:14:34 by sosmiyat          #+#    #+#             */
/*   Updated: 2025/01/04 16:26:59 by miyatasoujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

static char	*make_line_buffer(int fd, char *reminder, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read >= 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (reminder)
		{
			tmp = reminder;
			reminder = ft_strjoin(tmp, buffer);
			free(tmp);
		}
		else
			reminder = ft_strdup(buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0)
		reminder = NULL;
	return (reminder);
}

static char	*sep_line_buffer_to_line(char *line_buffer)
{
	char	*line;
	int		i;

	if (!line_buffer || !line_buffer[0])
		return (NULL);
	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
	{
		i++;
	}
	if (line_buffer[i] == '\n')
	{
		line = ft_strdup(&line_buffer[i + 1]);
		line_buffer[i + 1] = '\0';
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*buffer;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((long)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	reminder = make_line_buffer(fd, reminder, buffer);
	free(buffer);
	if (!reminder || reminder[0] == '\0')
	{
		free(reminder);
		return (NULL);
	}
	line = ft_strdup(reminder);
	tmp = reminder;
	reminder = sep_line_buffer_to_line(line);
	free(tmp);
	return (line);
}
