/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:19:24 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/02 12:36:54 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If quotes are found, we check if they are actually valid quotes inside
// quote_tab. If they are, we copy everything between the starting
// and end quote, but not the quotes themselves, returning the end
// of the quoted part to continue copying the string.
static char	*copy_quote_content(t_ptr_tab quote_tab, char **str, char *word_str,
								size_t *len)
{
	ssize_t	quote_i;

	quote_i = ft_tabfind(word_str, quote_tab, t);
	if (quote_i >= 0)
	{
		while (++word_str != quote_tab.end[quote_i] - 1)
			*((*str)++) = *(word_str);
		*len -= 2;
		return (quote_tab.end[quote_i]);
	}
	return (word_str);
}

// Iterate over the string word_str and copy it into str, skipping any quotes.
static char	*unquote_rewrite(t_mini *msh, char *word_str, size_t len)
{
	char	*str;
	char	*orig;

	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	orig = str;
	while (str < &orig[len])
	{
		while (*word_str && !quote_char(*word_str) && !ft_isspace(*word_str))
			*str++ = *word_str++;
		while (*word_str && quote_char(*word_str))
		{
			if (*word_str == '\'')
				word_str = copy_quote_content(*msh->squote_tab,
						&str, word_str, &len);
			else
				word_str = copy_quote_content(*msh->dquote_tab,
						&str, word_str, &len);
		}
	}
	return (orig);
}

// Check if the word contains quotes and rewrite them, setting a boolean
// that signals for later freeing of the allocated memory in unquote_rewrite()
static void	unquote_word(t_mini *msh, t_token *tok, size_t i)
{
	const size_t	len = msh->word_tab->end[i] - msh->word_tab->start[i];

	if (ft_strnchr(msh->word_tab->start[i], '\'', len)
		|| ft_strnchr(msh->word_tab->start[i], '\"', len))
	{
		tok->start = unquote_rewrite(msh, msh->word_tab->start[i], len);
		tok->end = tok->start + ft_strlen(tok->start);
		tok->rewritten = t;
	}
	else
	{
		tok->start = msh->word_tab->start[i];
		tok->end = msh->word_tab->end[i];
	}
}

// This function creates a linked list node in which a t_token resides.
// First, we check the token type based on a few conditions. Then,
// if it's a word and it contains known quotes, we rewrite the word
// without quotes and a boolean is set true, signalling that the rewritten
// string has to be freed later as it was allocated here.
static t_node	*create_token(t_mini *msh, t_ptr_tab *tab,
							size_t i, t_token_type prev)
{
	t_token				tok;
	t_node				*node;
	const t_token_type	type = find_token_type(tab->start[i], prev,
			&msh->cmd_since_last_pipe, *msh->redir_tab);

	tok.type = type;
	tok.rewritten = f;
	if (is_word_type(type))
		unquote_word(msh, &tok, i);
	else
	{
		tok.start = tab->start[i];
		tok.end = tab->end[i];
	}
	node = ft_lstnew_node(sizeof(t_token), &tok);
	return (node);
}

// The lexer iterates over inputted arguments and does syntax classification.
// It first locates redirections and words and then creates a token list
// which contains syntactical units called tokens. Thus, we obtain a data
// structure that lets us parse whatever the user inputted. The main logic
// compares pointers of the redir table against pointers of the word table,
// checking which pointer of their respective indexes comes first. This way,
// we don't have to guess the order of words and redirections.
t_list	*lexer(t_mini *msh)
{
	t_list	*tok_list;
	t_node	*curr_token;
	size_t	redir_i;
	size_t	word_i;

	msh->cmd_since_last_pipe = f;
	tok_list = ft_lstnew_list(sizeof(t_token));
	if (!tok_list)
		return (NULL);
	if (locate_redirs(msh->input, msh) < 0 || locate_words(msh->input, msh) < 0)
		return (ft_lstdel_list(tok_list, free_tok_list));
	redir_i = 0;
	word_i = 0;
	while ((msh->redir_tab->count > 0 && msh->redir_tab->start[redir_i])
		|| (msh->word_tab->count > 0 && msh->word_tab->start[word_i]))
	{
		if (ft_tabcmp(msh->redir_tab, msh->word_tab, redir_i, word_i))
			curr_token = create_token(msh,
					msh->redir_tab, redir_i++, get_token_type(tok_list->tail));
		else if (ft_tabcmp(msh->word_tab, msh->redir_tab, word_i, redir_i))
			curr_token = create_token(msh,
					msh->word_tab, word_i++, get_token_type(tok_list->tail));
		ft_lstadd_back(tok_list, curr_token);
	}
	return (tok_list);
}
