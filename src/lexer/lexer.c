/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:19:24 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/23 18:59:23 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	cmd_or_arg_word(t_token_type prev)
{
	if (is_redir_type(prev)
		|| is_word_type(prev))
		return (TOKEN_WORD_ARG);
	else
		return (TOKEN_WORD_CMD);
}

static t_token_type	find_token_type(char *start, t_token_type prev)
{
	const size_t	redir_len = is_redir(start);

	if (redir_len > 0)
	{
		if (*start == '|')
			return (TOKEN_PIPE);
		else if (*start == '>')
		{
			if (redir_len == 2)
				return (TOKEN_REDIR_APPEND);
			else
				return (TOKEN_REDIR_OUT);
		}
		else if (*start == '<')
		{
			if (redir_len == 2)
				return (TOKEN_REDIR_HEREDOC);
			else
				return (TOKEN_REDIR_IN);
		}
		else
			return (TOKEN_NULL);
	}
	return (cmd_or_arg_word(prev));
}

static t_node	*create_token(size_t data_size, t_ptr_tab *tab,
							size_t i, t_token_type prev)
{
	t_token				tok;
	t_node				*node;
	const t_token_type	type = find_token_type(tab->start[i], prev);

	tok.type = type;
	tok.start = tab->start[i];
	tok.end = tab->end[i];
	node = ft_lstnew_node(data_size, &tok);
	return (node);
}

static t_list	*tokenize(t_ptr_tab *redir_tab, t_ptr_tab *word_tab)
{
	t_list			*tok_list;
	t_node			*curr_token;
	t_token_type	prev_type;
	size_t			redir_i;
	size_t			word_i;

	tok_list = ft_lstnew_list(sizeof(t_token));
	if (!tok_list)
		return (NULL);
	redir_i = 0;
	word_i = 0;
	while (redir_tab->start[redir_i] || word_tab->start[word_i])
	{
		prev_type = get_token_type(tok_list->tail);
		if (ft_tabcmp(redir_tab, word_tab, redir_i, word_i))
			curr_token = create_token(tok_list->data_size,
					redir_tab, redir_i++, prev_type);
		else if (ft_tabcmp(word_tab, redir_tab, word_i, redir_i))
			curr_token = create_token(tok_list->data_size,
					word_tab, word_i++, prev_type);
		ft_lstadd_back(tok_list, curr_token);
	}
	return (tok_list);
}

t_list	*lexer(char *args, t_mini *msh)
{
	t_list	*token_list;

	search_quotes_candidates(msh->squote_tab, '\'');
	search_quotes_candidates(msh->dquote_tab, '\"');
	locate_redirs(args, msh);
	locate_words(args, msh);
	token_list = tokenize(msh->redir_tab, msh->word_tab);
	return (token_list);
}
