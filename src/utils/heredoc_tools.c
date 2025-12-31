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

static ssize_t	count_variables(char *line)
{
	char	*var_can;
	ssize_t	count;

	var_can = ft_strchr(line, '$');
	count = 0;
	while (var_can)
	{
		count += is_variable(var_can) > 0;
		var_can = ft_strchr(var_can + 1, '$');
	}
	return (count);
}

static char	**split_line(char *line, ssize_t count)
{
	char	**segments;
	char	*var_can;
	ssize_t	var_len;
	ssize_t	i;

	segments = ft_calloc(count + 4, sizeof(char *));
	if (!segments)
		return (NULL);
	i = 0;
	var_can = ft_strchr(line, '$');
	while (var_can && i < count + 3)
	{
		var_len = is_variable(var_can);
		if (var_len > 0)
		{
			if (line < var_can)
			{
				segments[i++] = ft_strndup(line, var_can - line);
				line = var_can + var_len + 1;
			}
			segments[i++] = ft_strndup(var_can, var_len + 1);
		}
		var_can = ft_strchr(var_can + 1, '$');
	}
	if (i < count + 3)
		segments[i] = ft_strdup(line);
	return (segments);
}

static char	*expand_line_vars(char *line, t_list *env_list)
{
	const ssize_t	count = count_variables(line);
	char			**split;

	if (count > 0)
	{
		split = split_line(line, count);
		(void)split;
		(void)env_list;
	}
	return (line);
}

int	heredoc(char *lim, t_list *env_list)
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
		line = expand_line_vars(line, env_list);
		write(heredoc_fd, line, ft_strlen(line));
		free(line);
	}
	close(heredoc_fd);
	return (0);
}
