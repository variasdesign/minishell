/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:19:24 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/05 21:14:06 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unquote_word(t_mini *msh, t_token *tok,
						t_ptr_tab *word_tab, size_t i)
{
}

// TODO: If is_word_type(type), remove quotes if they belong to
// squote_tab or dquote_tab before creating the token node
static t_node	*create_token(t_mini *msh, t_ptr_tab *tab,
							size_t i, t_token_type prev)
{
	t_token				tok;
	t_node				*node;
	const t_token_type	type = find_token_type(tab->start[i], prev);

	tok.type = type;
	if (is_word_type(type))
		unquote_word(msh, &tok, tab, i);
	else
	{
		tok.start = tab->start[i];
		tok.end = tab->end[i];
	}
	node = ft_lstnew_node(sizeof(t_token), &tok);
	return (node);
}

static t_list	*tokenize(t_mini *msh)
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
	while ((msh->redir_tab->count > 0 && msh->redir_tab->start[redir_i])
		|| (msh->word_tab->count > 0 && msh->word_tab->start[word_i]))
	{
		prev_type = get_token_type(tok_list->tail);
		if (ft_tabcmp(msh->redir_tab, msh->word_tab, redir_i, word_i))
			curr_token = create_token(msh,
					msh->redir_tab, redir_i++, prev_type);
		else if (ft_tabcmp(msh->word_tab, msh->redir_tab, word_i, redir_i))
			curr_token = create_token(msh,
					msh->word_tab, word_i++, prev_type);
		ft_lstadd_back(tok_list, curr_token);
	}
	return (tok_list);
}

// TODO: Error check redir_tab and word_tab count before calling tokenize
t_list	*lexer(t_mini *msh)
{
	t_list	*token_list;

	msh->redir_tab->count = locate_redirs(msh->input, msh);
	msh->word_tab->count = locate_words(msh->input, msh);
	token_list = tokenize(msh);
	return (token_list);
}
