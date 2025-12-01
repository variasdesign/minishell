/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_locate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:08:30 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/17 19:08:32 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_char(char c)
{
	return (ft_isspace(c) || quote_char(c) || redir_char(c));
}

// Count words by checking if they are valid. Invalid words will
// return word_len = 0. Words inside single or double quotes are counted as one.
static ssize_t	count_words(char *args, t_ptr_tab squote_tab,
								t_ptr_tab dquote_tab)
{
	ssize_t	count;
	ssize_t	squote_i;
	ssize_t	dquote_i;
	char	*str;

	count = 0;
	str = args;
	while (*str)
	{
		while (*str && (check_char(*str)))
			str++;
		if (!*str)
			break ;
		squote_i = ft_tabfind(str, squote_tab);
		dquote_i = ft_tabfind(str, dquote_tab);
		if (squote_i >= 0)
			str = squote_tab.end[squote_i];
		if (dquote_i >= 0)
			str = dquote_tab.end[dquote_i];
		while (*str && !check_char(*str))
			str++;
		count++;
	}
	return (count);
}

// FIX: echo 'hello'hello produces echo hello
// The problem lies in how the words-inside-quotes logic works.
// Words can continue after quotes and should be taken into account
// as a single word. But just extending until end of words would
// duplicate the quotes when token list is generated.
// So either we change the token list generation logic by checking
// presence of quotes against their respective pointer tables,
// or we remove quotes on-the-fly whenever needed.
// e.g. echo 'hello'hello
// current behavior: echo hello
// behavior after extending until end of words: echo hello'hello
// correct behavior: echo hellohello
static char	*check_words_inside_quotes(t_mini *msh, char *word_can, ssize_t i)
{
	ssize_t	squote_i;
	ssize_t	dquote_i;

	msh->word_tab->start[i] = word_can;
	squote_i = ft_tabfind(word_can, *msh->squote_tab);
	dquote_i = ft_tabfind(word_can, *msh->dquote_tab);
	if (squote_i >= 0)
	{
		word_can = msh->squote_tab->end[squote_i];
		msh->word_tab->end[i] = msh->squote_tab->end[squote_i] - 1;
	}
	else if (dquote_i >= 0)
	{
		msh->word_tab->end[i] = msh->dquote_tab->end[dquote_i] - 1;
		word_can = msh->dquote_tab->end[dquote_i];
	}
	else
	{
		while (*word_can && !check_char(*word_can))
			word_can++;
		msh->word_tab->end[i] = word_can;
	}
	return (word_can);
}

static void	search_word_candidates(t_mini *msh)
{
	char	*word_can;
	ssize_t	i;

	word_can = (char *)msh->word_tab->orig;
	i = -1;
	while (*word_can && ++i < msh->word_tab->count)
	{
		while (*word_can && check_char(*word_can))
			word_can++;
		if (!*word_can)
			break ;
		word_can = check_words_inside_quotes(msh, word_can, i);
	}
}

// Locate every word and store its start and end in a pointer table.
// start is a pointer to first char, end is a pointer to next char of last.
// Example:	cat "file with spaces" | sort -n\0
// 			|  | |               |   |   || |
// 			orig |               |   start[2]
// 			|  | |               |       || |
// 			start[0]             end[1]  end[2]
// 			   | |                        | |
// 			   end[0]                     start[3]
// 			     |                          |
// 			     start[1]                   end[3]
// TODO: Read on IFS (internal field separator)
// https://www.baeldung.com/linux/ifs-shell-variable
ssize_t	locate_words(char *args, t_mini *msh)
{
	msh->word_tab->count = count_words(args, *msh->squote_tab,
			*msh->dquote_tab);
	if (msh->word_tab->count > 0)
	{
		msh->word_tab = ft_taballoc(msh->word_tab, args, sizeof(char *));
		if (!msh->word_tab)
		{
			perror("Error allocating word pointer table");
			return (-1);
		}
		search_word_candidates(msh);
	}
	if (msh->word_tab->count < 0)
		printf("Error locating words.\n");
	return (msh->word_tab->count);
}
