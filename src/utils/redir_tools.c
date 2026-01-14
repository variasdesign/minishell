/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 23:15:58 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/14 23:15:59 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Custom strchr that looks for the first available redirection, if any.
char	*redir_strchr(char *args)
{
	char	*pipe;
	char	*in;
	char	*out;

	pipe = ft_strchr(args, '|');
	in = ft_strchr(args, '<');
	out = ft_strchr(args, '>');
	if (pipe && (!in || pipe < in) && (!out || pipe < out))
		return (pipe);
	else if (in && (!pipe || in < pipe) && (!out || in < out))
		return (in);
	else if (out && (!pipe || out < pipe) && (!in || out < in))
		return (out);
	return (NULL);
}

int	redir_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

// Perform preliminary redir validation
ssize_t	is_redir(char *redir)
{
	const char	c = *redir;
	const char	next_char = *(redir + 1);
	size_t		len;
	size_t		max_len;

	len = 0;
	if (redir_char(c))
	{
		max_len = 2 - (c == '|');
		if (c == '>' && next_char == '|')
			return (2);
		while (len < max_len && redir[len] == c)
			len++;
	}
	return (len);
}

// Obtain the path inputted as a redirection argument
char	*get_redir_path(t_node *redir_node)
{
	t_redir	*redir;

	redir = redir_node->content;
	return (redir->file);
}
