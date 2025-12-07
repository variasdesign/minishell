/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:18:52 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/01 12:19:12 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(void)
{
	int	hd_fd;

	hd_fd = open("/tmp/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (hd_fd < 0)
	{
		ft_perror(E_HEREDOC_FAILURE, NULL, f, 0);
		return (-1);
	}
	return (hd_fd);
}

int	heredoc(char *lim)
{
	const int	heredoc_fd = open_heredoc();
	const int	lim_len = ft_strlen(lim);
	char		*line;

	if (heredoc_fd < 0)
		return (-1);
	while (t)
	{
		line = get_next_line(0);
		if (!line)
		{
			ft_perror(E_HEREDOC_FAILURE, NULL, f, 0);
			return (-1);
		}
		if (!ft_strncmp(line, lim, lim_len) && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
		free(line);
	}
	close(heredoc_fd);
	return (0);
}
