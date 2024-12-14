/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sousuke <sousuke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:50:44 by sousuke           #+#    #+#             */
/*   Updated: 2024/12/15 02:01:22 by sousuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
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

char	*_fill_line_buffer(int fd, char *reminder, char *buffer)
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

char	*_set_line(char *line_buffer)
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

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = malloc((long)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	reminder = _fill_line_buffer(fd, reminder, buffer);
	free(buffer);
	if (!reminder || reminder[0] == '\0')
	{
		free(reminder);
		reminder = NULL;
		return (NULL);
	}
	line = ft_strdup(reminder);
	tmp = reminder;
	reminder = _set_line(line);
	free(tmp);
	return (line);
}
