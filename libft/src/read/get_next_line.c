/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:39:32 by varias-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:39:52 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	found_newline(char *remaining_chars)
{
	ssize_t		i;

	i = 0;
	while (remaining_chars[i] != '\n' && remaining_chars[i])
		i++;
	if (remaining_chars[i] == '\n')
		return (i);
	else
		return (-1);
}

char	*append_buffer_to_line(char *line, char *remaining_chars, size_t len)
{
	char	*tmp;
	char	trunc_buffer[BUFFER_SIZE + 1];
	size_t	i;

	ft_strlcpy(&trunc_buffer[0], remaining_chars, len + 1);
	if (!line)
	{
		line = ft_calloc(ft_strlen(trunc_buffer) + 1, sizeof(char));
		if (!line)
			return (NULL);
		i = 0;
		while (trunc_buffer[i])
		{
			line[i] = trunc_buffer[i];
			i++;
		}
	}
	else
	{
		tmp = line;
		line = ft_strjoin(line, trunc_buffer);
		free(tmp);
		tmp = NULL;
	}
	return (line);
}

t_bool	set_line(char **line, char *remaining_chars)
{
	ssize_t	i;
	size_t	remaining_len;

	i = found_newline(remaining_chars) + 1;
	if (i > 0)
	{
		*line = append_buffer_to_line(*line, remaining_chars,
				i);
		remaining_len = (BUFFER_SIZE + 1) - i;
		ft_strlcpy(remaining_chars, &remaining_chars[i],
			remaining_len + 1);
		return (t);
	}
	else
	{
		*line = append_buffer_to_line(*line, remaining_chars, BUFFER_SIZE + 1);
		ft_strlcpy(remaining_chars, "", BUFFER_SIZE);
	}
	return (f);
}

char	*read_into_buffer(int fd, char *remaining_chars)
{
	ssize_t	read_count;
	char	*line;
	t_bool	newline;

	line = NULL;
	read_count = 1;
	newline = f;
	while (read_count > 0 && !newline)
	{
		if (!remaining_chars[0])
		{
			read_count = read(fd, remaining_chars, BUFFER_SIZE);
			if (read_count == -1)
				return (NULL);
			if (read_count == 0)
				return (line);
			remaining_chars[read_count] = 0;
		}
		newline = set_line(&line, &remaining_chars[0]);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	remaining_chars[__FD_SETSIZE][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd > __FD_SETSIZE || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_into_buffer(fd, remaining_chars[fd]);
	return (line);
}
