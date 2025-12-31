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

int	redir_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

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

char	*get_redir_path(t_node *redir_node)
{
	t_redir	*redir;

	redir = redir_node->content;
	return (redir->file);
}
