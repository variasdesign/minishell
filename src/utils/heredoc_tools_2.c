/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:54:14 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/14 20:01:17 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*reassemble_line(char **split)
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

static char	*expand_heredoc_var(char **split, size_t i, t_list *env_list)
{
	char	*tmp_env;
	t_env	*env;

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
	return (split[i]);
}

char	*expand_line_vars(char *line, t_list *env_list, t_bool expand_vars)
{
	const ssize_t	count = count_variables(line);
	char			**split;
	size_t			i;

	if (count > 0 && expand_vars)
	{
		i = 0;
		split = split_line(line, count);
		while (split[i])
		{
			if (split[i][0] == '$' && is_variable(split[i]))
				split[i] = expand_heredoc_var(split, i, env_list);
			i++;
		}
		free(line);
		line = reassemble_line(split);
	}
	return (line);
}
