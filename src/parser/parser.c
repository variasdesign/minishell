/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:09 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/24 18:19:34 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(t_node *node)
{
	t_token *token;

	if (node)
	{
		token = node->content;
		return (token->type);
	}
	else
		return (TOKEN_NULL);
}

static t_node	*create_cmd(t_node *token_node)
{
	t_cmd			cmd;
	t_node			cmd_node;
	size_t			words;

	cmd.in = 0;
	cmd.out = 1;
	if (token_node)
	{
		words = 1;
		token_node = token_node->next;
	}
	else
		 return (NULL);
}

t_node	*find_token_node(t_node *offset, t_token_type type)
{
	t_node	*node;

	node = offset;
	while (node)
	{
		if (get_token_type(node) == type)
			return (node);
		node = node->next;
	}
	return (NULL);
}

static size_t	count_word_groups(t_list token_list)
{
	t_node	*curr_node;
	size_t	count;

	count = 0;
	curr_node = find_token_node(token_list.head, TOKEN_WORD);
	while (curr_node)
	{
		while (curr_node && get_token_type(curr_node) != TOKEN_PIPE)
			curr_node = curr_node->next;
		count++;
		curr_node = find_token_node(curr_node, TOKEN_WORD);
	}
	return (count);
}

// TODO: Redir and word validation: Prompts can't start or end with a redir,
// and (if I'm not mistaken) there should be more words than redirs.
// TODO: Heredoc goes first before output and input redirs, even if it's last on prompt
t_list	*parser(t_list *token_list)
{
	t_list	*cmd_list;
	t_node	*token_node;
	t_node	*cmd_node;
	size_t	word_groups;

	if (!validate_token_list(*token_list))
	{
		printf("Invalid prompt.\n");
		ft_lstdel_list(token_list, free);
		return (NULL);
	}
	cmd_list = ft_lstnew_list(sizeof(t_cmd));
	word_groups = count_word_groups(*token_list);
	token_node = find_token_node(token_list->head, TOKEN_WORD);
	while (word_groups > 0 && token_node)
	{
		cmd_node = create_cmd(token_node);
		ft_lstadd_back(cmd_list, cmd_node);
		token_node = find_token_node(token_node->next, TOKEN_WORD);
		word_groups--;
	}
	ft_lstdel_list(token_list, free);
	return (cmd_list);
}
