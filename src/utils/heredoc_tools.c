/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:18:52 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 19:01:19 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(void)
{
	int	hd_fd;

	hd_fd = open("/tmp/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0664);
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
				segments[i++] = ft_strndup(line, var_can - line);
			segments[i++] = ft_strndup(var_can, var_len + 1);
			line = var_can + var_len + 1;
		}
		var_can = ft_strchr(var_can + 1, '$');
	}
	if (i < count + 3)
		segments[i] = ft_strdup(line);
	return (segments);
}

static char *reassemble_line(char **split)
{
	size_t	i;
	int		new_len;
	char	*line;

	new_len = 0;
	i = 0;
	while (split[i])
		new_len += ft_strlen(split[i++]);
	line = ft_calloc(new_len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (split[i])
		ft_strlcat(line, split[i++], new_len + 1);
	ft_freematrix((void **)split);
	return (line);
}

static char	*expand_line_vars(char *line, t_list *env_list, t_bool expand_vars)
{
	const ssize_t	count = count_variables(line);
	char			**split;
	size_t	i;
	char			*tmp_env;
	t_env			*env;

	if (count > 0 && expand_vars)
	{
		i = 0;
		split = split_line(line, count);
		while (split[i])
		{
			if (split[i][0] == '$')
			{
				if (is_variable(split[i]))
				{
					if (split[i][1] && split[i][1] != '?')
					{
						tmp_env = ft_strndup(&split[i][1], ft_strlen(&split[i][1]));
						env = get_env(env_list, tmp_env);
						free(split[i]);
						if (!env)
							split[i] = ft_strdup("");
						else
							split[i] = ft_strdup(env->value);
						free(tmp_env);
					}
					else if (split[i][1] == '?')
					{
						free(split[i]);
						split[i] = ft_itoa(g_sig);
					}
				}
			}
			i++;
		}
		line = reassemble_line(split);
	}
	return (line);
}

/// FIX: Unlink /tmp/heredoc when heredoc finishes.
int	heredoc(char *lim, t_list *env_list, t_bool expand_vars)
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
		line = expand_line_vars(line, env_list, expand_vars);
		write(heredoc_fd, line, ft_strlen(line));
		free(line);
	}
	close(heredoc_fd);
	return (0);
}
