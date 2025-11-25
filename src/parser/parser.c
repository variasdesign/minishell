/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:09 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/21 13:58:59 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redir_node(t_list *redir_list, t_list *token_list,
						t_token_type type, t_redir *redir)
{
	t_node	*redir_node;

	redir_node = find_token_node(token_list->head, type, f);
	while (redir_node)
	{
		redir->type = get_token_type(redir_node);
		redir->file = token_content(redir_node->next);
		ft_lstdel_wrapper(token_list, redir_node->next, free);
		redir_node = ft_lstnew_node(redir_list->data_size, redir);
		ft_lstadd_back(redir_list, redir_node);
		redir_node = find_token_node(redir_node->next, type, f);
	}
}

static t_list	*init_redir_list(t_list *token_list, t_node *token_node)
{
	t_list			*redir_list;
	t_redir			redir;

	redir_list = ft_lstnew_list(sizeof(t_redir));
	if (token_node == find_token_node(token_list->head, TOKEN_WORD_CMD, f))
		add_redir_node(redir_list, token_list, TOKEN_REDIR_IN_ALL, &redir);
	if (token_node == find_token_node(token_list->tail, TOKEN_WORD_CMD, t))
		add_redir_node(redir_list, token_list, TOKEN_REDIR_OUT_ALL, &redir);
	if (redir_list->count < 1)
	{
		ft_lstdel_list(redir_list, free);
		return (NULL);
	}
	return (redir_list);
}

static char	**insert_words_into_args(t_node *token_node, size_t word_count)
{
	char	**args;
	size_t	i;

	args = ft_calloc(word_count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < word_count && token_node)
	{
		args[i++] = token_content(token_node);
		token_node = find_token_node(token_node->next, TOKEN_WORD_ARG, f);
	}
	return (args);
}

static t_node	*create_cmd(t_list *token_list, t_node *token_node)
{
	t_cmd	cmd;
	t_node	*cmd_node;

	if (token_node)
	{
		cmd.redir_list = init_redir_list(token_list, token_node);
		cmd.args = insert_words_into_args(token_node,
				count_word_tokens(token_node));
		if (!cmd.args)
			return (NULL);
		cmd.fd_in = 0;
		cmd.fd_out = 1;
		cmd_node = ft_lstnew_node(sizeof(t_cmd), &cmd);
		return (cmd_node);
	}
	else
		return (NULL);
}

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
	token_node = find_token_node(token_list->head, TOKEN_WORD_CMD, f);
	while (word_groups > 0 && token_node)
	{
		cmd_node = create_cmd(token_list, token_node);
		ft_lstadd_back(cmd_list, cmd_node);
		token_node = find_token_node(token_node->next, TOKEN_WORD_CMD, f);
		word_groups--;
	}
	ft_lstdel_list(token_list, free);
	return (cmd_list);
}
