/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:16:54 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/01 13:33:03 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count word groups by counting number of pipes. Word groups are groups led
// by a TOKEN_WORD_CMD and optionally any following TOKEN_WORD_ARG. Since pipes
// separate groups of words (and thus, commands), we can use the number
// of pipes as an indicator of word groups, given that word_groups = pipes + 1.
size_t	count_word_groups(t_list token_list)
{
	t_node	*curr_node;
	size_t	count;

	count = 1;
	curr_node = find_token_node(token_list.head, TOKEN_PIPE, f);
	while (curr_node)
	{
		count++;
		curr_node = find_token_node(curr_node->next, TOKEN_PIPE, f);
	}
	return (count);
}

// Count how many word token are from a given token_node
size_t	count_word_tokens(t_node *token_node)
{
	size_t			words;
	t_token_type	type;

	words = 0;
	type = get_token_type(token_node);
	while (token_node && type != TOKEN_PIPE)
	{
		if (is_word_type(type))
			words++;
		token_node = token_node->next;
		type = get_token_type(token_node);
	}
	return (words);
}

// Obtain token type from a given token node.
t_token_type	get_token_type(t_node *node)
{
	t_token	*token;

	if (node)
	{
		token = node->content;
		return (token->type);
	}
	return (TOKEN_NULL);
}

// Allocate a string that contains the token string, used when converting
// from token list to command list.
char	*dup_token_content(t_node *node)
{
	const t_token	*token = node->content;
	const char		*start = token->start;
	const char		*end = token->end;
	const size_t	len = end - start;
	char			*str;

	str = ft_strndup(start, len);
	return (str);
}

// Return a node that contains a token of t_token_type type. There's also
// the special types TOKEN_WORD_ALL, TOKEN_REDIR_IN_ALL and TOKEN_REDIR_OUT_ALL
// to signal any token of their respective categories. Also, the boolean
// last signals if we are searching from first to last or last to first.
t_node	*find_token_node(t_node *node, t_token_type type, t_bool last)
{
	t_token_type	node_type;

	while (node)
	{
		node_type = get_token_type(node);
		if (node_type == type)
			return (node);
		else if (type == TOKEN_REDIR_IN_ALL
			&& (node_type == TOKEN_REDIR_IN
				|| node_type == TOKEN_REDIR_HEREDOC))
			return (node);
		else if (type == TOKEN_REDIR_OUT_ALL
			&& (node_type == TOKEN_REDIR_OUT
				|| node_type == TOKEN_REDIR_APPEND))
			return (node);
		else if (type == TOKEN_WORD_ALL
			&& (node_type == TOKEN_WORD_CMD
				|| node_type == TOKEN_WORD_ARG))
			return (node);
		if (last)
			node = node->prev;
		else
			node = node->next;
	}
	return (NULL);
}
