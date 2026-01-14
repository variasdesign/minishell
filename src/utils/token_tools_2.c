/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:10:41 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/05 21:11:04 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if we are actually dealing with a command word or an argument word.
// If the previous token is a redirection or cmd_since_last_pipe is set to true
// then it's a TOKEN_WORD_ARG. Else, it's a TOKEN_WORD_CMD.
static t_token_type	cmd_or_arg_word(t_token_type prev,
									t_bool *cmd_since_last_pipe)
{
	if (is_redir_type(prev) || *cmd_since_last_pipe)
		return (TOKEN_WORD_ARG);
	*cmd_since_last_pipe = t;
	return (TOKEN_WORD_CMD);
}

// Check against clobber redirection >|
static t_token_type	redir_out_type(size_t redir_len, char *start)
{
	if (redir_len == 2)
	{
		if (*(start + 1) == '|')
			return (TOKEN_REDIR_OUT);
		return (TOKEN_REDIR_APPEND);
	}
	return (TOKEN_REDIR_OUT);
}

// Assign a token type to a given string. First, check if start is inside
// the redir table. If it is, try to guess which redir type is by looking at
// its characters. If not, it must be a word.
t_token_type	find_token_type(char *start, t_token_type prev,
							t_bool *cmd_since_last_pipe, t_ptr_tab redir_tab)
{
	const size_t	redir_len = is_redir(start);

	if (redir_len > 0 && ft_tabfind(start, redir_tab, t) >= 0)
	{
		if (*start == '|')
		{
			*cmd_since_last_pipe = f;
			return (TOKEN_PIPE);
		}
		else if (*start == '>')
			return (redir_out_type(redir_len, start));
		else if (*start == '<')
		{
			if (redir_len == 2)
				return (TOKEN_REDIR_HEREDOC);
			return (TOKEN_REDIR_IN);
		}
		else
			return (TOKEN_NULL);
	}
	return (cmd_or_arg_word(prev, cmd_since_last_pipe));
}
