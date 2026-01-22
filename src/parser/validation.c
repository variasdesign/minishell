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

// Validate pipes by looking if the previous and next tokens are words.
static t_bool	validate_pipes(t_list token_list)
{
	t_node	*curr_node;
	char	*token_str;

	curr_node = find_token_node(token_list.head, TOKEN_PIPE, f);
	while (curr_node)
	{
		if (get_token_type(curr_node) == TOKEN_PIPE)
		{
			if (curr_node->next)
			{
				if (!(is_word_type(get_token_type(curr_node->prev))))
				{
					token_str = dup_token_content(curr_node->next);
					ft_printf(2, E_INVALID_PROMPT, token_str);
					free(token_str);
					return (f);
				}
			}
			else
				return (ft_printf(2, E_INVALID_PROMPT, "newline"), f);
		}
		curr_node = find_token_node(curr_node->next, TOKEN_PIPE, f);
	}
	return (t);
}

// Validate redirections by looking for a word argument after
// the current redir token. If something fails, print the unexpected token.
static t_bool	validate_redirs(t_list token_list)
{
	t_node	*curr_node;
	char	*token_str;

	curr_node = token_list.head;
	while (curr_node)
	{
		if (is_redir_type(get_token_type(curr_node)))
		{
			if (curr_node->next)
			{
				if (!(is_word_type(get_token_type(curr_node->next))))
				{
					token_str = dup_token_content(curr_node->next);
					ft_printf(2, E_INVALID_PROMPT, token_str);
					free(token_str);
					return (f);
				}
			}
			else
				return (ft_printf(2, E_INVALID_PROMPT, "newline"), f);
		}
		curr_node = curr_node->next;
	}
	return (t);
}

// Validate words by checking if there are any pipes before the first word.
// If something fails, print the unexpected token.
static t_bool	validate_words(t_list token_list)
{
	t_node	*curr_node;
	t_node	*first_word;
	char	*token_str;

	curr_node = token_list.head;
	first_word = find_token_node(curr_node, TOKEN_WORD_ALL, f);
	if (curr_node && first_word && curr_node != first_word)
	{
		curr_node = first_word->prev;
		while (curr_node)
		{
			if (get_token_type(curr_node) == TOKEN_PIPE)
			{
				token_str = dup_token_content(curr_node);
				ft_printf(2, E_INVALID_PROMPT, token_str);
				free(token_str);
				return (f);
			}
			curr_node = curr_node->prev;
		}
	}
	return (t);
}

t_bool	validate_token_list(t_list token_list)
{
	if (!validate_words(token_list)
		|| !validate_redirs(token_list)
		|| !validate_pipes(token_list))
	{
		g_sig = 2;
		return (f);
	}
	return (t);
}
