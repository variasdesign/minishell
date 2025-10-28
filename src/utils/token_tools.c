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
	const char		*end = token->start;
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
