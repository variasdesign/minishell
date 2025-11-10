/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:16:54 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/28 18:17:53 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_word_groups(t_list token_list)
{
	t_node	*curr_node;
	size_t	count;

	count = 0;
	curr_node = find_token_node(token_list.head, TOKEN_WORD_CMD, f);
	while (curr_node)
	{
		count++;
		curr_node = find_token_node(curr_node->next, TOKEN_WORD_CMD, f);
	}
	return (count);
}

size_t	count_word_tokens(t_node *cmd_node)
{
	size_t	words;

	words = 0;
	while (cmd_node && is_word_type(get_token_type(cmd_node)))
	{
		words++;
		cmd_node = cmd_node->next;
	}
	return (words);
}

t_token_type	get_token_type(t_node *node)
{
	t_token	*token;

	if (node)
	{
		token = node->content;
		return (token->type);
	}
	else
		return (TOKEN_NULL);
}

char	*token_content(t_node *node)
{
	const t_token	*token = node->content;
	const char		*start = token->start;
	const char		*end = token->end;
	const size_t	len = end - start;

	return (ft_strndup(start, len));
}

t_node	*find_token_node(t_node *offset, t_token_type type, t_bool last)
{
	t_node	*node;

	node = offset;
	while (node)
	{
		if (get_token_type(node) == type)
			return (node);
		if (last)
			node = node->prev;
		else
			node = node->next;
	}
	return (NULL);
}
