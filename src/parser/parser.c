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

static t_node	*create_cmd()
{
	t_cmd	cmd;

}

t_node	*find_token_node(t_list *list, t_node *offset, t_token_type type)
{
	t_node	*node;
	t_token	*tok;

	if (!offset)
		node = list->head;
	else
		node = offset;
	while (node)
	{
		tok = node->content;
		if (tok->type == type)
			return (node);
		node = node->next;
	}
	return (NULL);
}

// TODO: Redir and word validation: Prompts can't start or end with a redir,
// and (if I'm not mistaken) there should be more words than redirs.
t_list	*parser(t_list *token_list)
{
	t_list	*cmd_list;
	t_node	*curr_node;
	t_node	*curr_token;
	size_t	word_group_i;
	
	if (!validate_token_list(*token_list))
	{
		printf("Invalid prompt.\n");
		ft_lstdel_list(token_list, free);
		return (NULL);
	}
	// TODO: Command assembly
	cmd_list = ft_lstnew_list(sizeof(t_cmd));
	word_group_i = count_word_groups(token_list);
	curr_node = find_token_node(token_list, curr_node, TOKEN_WORD);
	while (word_group_i > 0)
	{
		curr_node = create_cmd(cmd_list, count_words());
		curr_node = find_token_node(token_list, curr_node->next, TOKEN_WORD);
		word_group_i--;
	}
	ft_lstdel_list(token_list, free);
	return (cmd_list);
}
