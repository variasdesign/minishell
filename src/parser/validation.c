/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:08:36 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/24 18:10:53 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	validate_pipes(t_list token_list)
{
	t_node	*curr_node;

	curr_node = find_token_node(token_list.head, TOKEN_PIPE);
	while (curr_node)
	{
		if (get_token_type(curr_node) == TOKEN_PIPE)
		{
			if (curr_node->prev && curr_node->next)
			{
				if (get_token_type(curr_node->prev) != TOKEN_WORD)
					return (f);
				if (get_token_type(curr_node->next) != TOKEN_WORD)
					return (f);
			}
			else
				return (f);
		}
		curr_node = find_token_node(curr_node->next, TOKEN_PIPE);
	}
	return (t);
}

t_bool	is_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_HEREDOC)
		return (t);
	return (f);
}

static t_bool	validate_redirs(t_list token_list)
{
	t_node	*curr_node;

	curr_node = token_list.head;
	while (curr_node)
	{
		if (is_redir_type(get_token_type(curr_node)))
		{
			if (curr_node->next)
			{
				if (get_token_type(curr_node->next) != TOKEN_WORD)
					return (f);
			}
			else
				return (f);
		}
		curr_node = curr_node->next;
	}
	return (t);
}

t_bool	validate_token_list(t_list token_list)
{
	if (!validate_pipes(token_list))
		return (f);
	else if (!validate_redirs(token_list))
		return (f);
	return (t);
}
