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
	t_list			*redir_list;
	t_token_type	type;

	redir_list = ft_lstnew_list(sizeof(t_redir));
	type = get_token_type(token_node);
	while (token_node && type != TOKEN_PIPE)
	{
		if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
			|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC)
			add_redir_node(redir_list, token_list, token_node);
		token_node = token_node->next;
		type = get_token_type(token_node);
	}
	if (redir_list->count < 1)
		return (ft_lstdel_list(redir_list, free));
	return (redir_list);
}

static char	**insert_words_into_args(t_node *token_node, size_t word_count)
{
	char			**args;
	t_token_type	type;
	size_t			i;

	type = get_token_type(token_node);
	args = ft_calloc(word_count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < word_count && token_node && type != TOKEN_PIPE)
	{
		if (is_word_type(type))
			args[i++] = dup_token_content(token_node);
		token_node = token_node->next;
		type = get_token_type(token_node);
	}
	return (args);
}

static t_node	*create_cmd(t_list *token_list, t_node **token_node,
						size_t curr_index, size_t last_index)
{
	t_cmd	ref;
	t_node	*cmd_node;

	if (*token_node)
	{
		ref.redir_list = init_redir_list(token_list, *token_node);
		ref.args = insert_words_into_args(*token_node,
				count_word_tokens(*token_node));
		if (!ref.args)
			return (NULL);
		ref.fd_in = STDIN_FILENO;
		ref.fd_out = STDOUT_FILENO;
		ref.pipe_from = curr_index != 0;
		ref.pipe_to = curr_index != last_index;
		cmd_node = ft_lstnew_node(sizeof(t_cmd), &ref);
		if (curr_index < last_index)
			*token_node = find_token_node((*token_node)->next,
					TOKEN_PIPE, f)->next;
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
	size_t	i;

	if (!validate_token_list(*token_list))
	{
		printf(E_INVALID_PROMPT);
		return (ft_lstdel_list(token_list, free));
	}
	cmd_list = ft_lstnew_list(sizeof(t_cmd));
	if (!cmd_list)
		return (ft_lstdel_list(token_list, free));
	word_groups = count_word_groups(*token_list);
	token_node = token_list->head;
	i = 0;
	while (i < word_groups && token_node)
	{
		cmd_node = create_cmd(token_list, &token_node, i, word_groups - 1);
		ft_lstadd_back(cmd_list, cmd_node);
		i++;
	}
	ft_lstdel_list(token_list, free);
	return (cmd_list);
}
