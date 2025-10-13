/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:22:57 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/11 18:23:46 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

ssize_t	is_redir(char *redir)
{
	const char	c = *redir;
	ssize_t		len;
	ssize_t		max_len;

	len = 0;
	if (is_redir_char(c))
	{
		max_len = 2 - c == '|';
		while (len < max_len && redir[len] == c)
			len++;
	}
	return (len);
}

// Process redirection operator and advance pointer
char	*process_redir(char *str, int redir_len, t_mini *msh, ssize_t *count)
{
	if (is_inside_quotes(str, msh))
	{
		// Operator inside quotes = counts as word
		(*count)++;
	}
	// Operator outside quotes = skip, don't count
	return (str + redir_len);
}

// Check if current position starts with a redirection operator
int	is_redir_start(char *str)
{
	if (!str || !*str)
		return (0);
	// Check for double operators first
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	// Check for single operators
	if (str[0] == '<' || str[0] == '>' || str[0] == '|')
		return (1);
	return (0);
}
