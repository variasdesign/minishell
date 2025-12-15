/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:09 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/15 21:01:35 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redir_node(t_list *redir_list, t_list *token_list,
						t_node *token_node)
{
	t_node	*redir_node;
	t_redir	redir;

	redir.type = get_token_type(token_node);
	redir.file = dup_token_content(token_node->next);
	ft_lstdel_wrapper(token_list, token_node->next, free);
	redir_node = ft_lstnew_node(redir_list->data_size, &redir);
	ft_lstadd_back(redir_list, redir_node);
}

static t_list	*init_redir_list(t_list *token_list, t_node *token_node)
{
	t_list	*redir_list;

	redir_list = ft_lstnew_list(sizeof(t_redir));
	while (token_node && get_token_type(token_node) != TOKEN_PIPE)
	{
		if (get_token_type(token_node) == TOKEN_REDIR_IN
			|| get_token_type(token_node) == TOKEN_REDIR_OUT
			|| get_token_type(token_node) == TOKEN_REDIR_APPEND
			|| get_token_type(token_node) == TOKEN_REDIR_HEREDOC)
			add_redir_node(redir_list, token_list, token_node);
		token_node = token_node->next;
	}
	if (redir_list->count < 1)
		return (ft_lstdel_list(redir_list, free));
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
		args[i] = dup_token_content(token_node);
		token_node = find_token_node(token_node->next, TOKEN_WORD_ARG, f);
		i++;
	}
	return (args);
}

static t_node	*create_cmd(t_list *token_list, t_node *token_node)
{
	t_cmd	ref;
	t_node	*cmd_node;

	if (token_node)
	{
		ref.redir_list = init_redir_list(token_list, token_node);
		ref.args = insert_words_into_args(token_node,
				count_word_tokens(token_node));
		if (!ref.args)
			return (NULL);
		ref.fd_in = STDIN_FILENO;
		ref.fd_out = STDOUT_FILENO;
		ref.pipe_from = token_node
			!= find_token_node(token_list->head, TOKEN_WORD_CMD, f);
		ref.pipe_to = token_node
			!= find_token_node(token_list->tail, TOKEN_WORD_CMD, t);
		cmd_node = ft_lstnew_node(sizeof(t_cmd), &ref);
		return (cmd_node);
	}
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
		printf(E_INVALID_PROMPT);
		return (ft_lstdel_list(token_list, free));
	}
	cmd_list = ft_lstnew_list(sizeof(t_cmd));
	if (!cmd_list)
		return (ft_lstdel_list(token_list, free));
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
