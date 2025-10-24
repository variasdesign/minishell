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
	t_token	*next_token;
	t_token	*curr_token;
	
	curr_token = token_list.tail->content;
	if (curr_token->type == TOKEN_PIPE)
		return (f);
	curr_token = token_list.head->content;
	if (curr_token->type == TOKEN_PIPE)
		return (f);
	curr_node = token_list.head;
	while (curr_node)
	{
		curr_token = (t_token *)curr_node->content;
		if (curr_token->type == TOKEN_PIPE)
		{
			next_token = (t_token *)curr_node->next->content;
			if (next_token->type != TOKEN_WORD)
				return (f);
		}
		curr_node = curr_node->next;
	}
	return (t);
}

static t_bool	validate_redirs(t_list token_list)
{
	t_node	*curr_node;
	t_token	*next_token;
	t_token	*curr_token;
	
	curr_node = token_list.head;
	while (curr_node)
	{
		curr_token = curr_node->content;
		if (curr_token->type == TOKEN_PIPE)
		{
			next_token = curr_node->next->content;
			if (next_token->type != TOKEN_WORD)
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
