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
	size_t		len;
	size_t		max_len;

	len = 0;
	if (redir_char(c))
	{
		max_len = 2 - (c == '|');
		while (len < max_len && redir[len] == c)
			len++;
	}
	return (len);
}
