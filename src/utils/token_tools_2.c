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

static t_token_type	cmd_or_arg_word(t_token_type prev)
{
	if (is_redir_type(prev)
		|| is_word_type(prev))
		return (TOKEN_WORD_ARG);
	else
		return (TOKEN_WORD_CMD);
}

t_token_type	find_token_type(char *start, t_token_type prev)
{
	const size_t	redir_len = is_redir(start);

	if (redir_len > 0)
	{
		if (*start == '|')
			return (TOKEN_PIPE);
		else if (*start == '>')
		{
			if (redir_len == 2)
				return (TOKEN_REDIR_APPEND);
			else
				return (TOKEN_REDIR_OUT);
		}
		else if (*start == '<')
		{
			if (redir_len == 2)
				return (TOKEN_REDIR_HEREDOC);
			else
				return (TOKEN_REDIR_IN);
		}
		else
			return (TOKEN_NULL);
	}
	return (cmd_or_arg_word(prev));
}
