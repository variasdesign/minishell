/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_locate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:08:30 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/03 18:14:00 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count words by checking if they are valid. Invalid words will
// return word_len = 0. Words inside single or double quotes are counted as one.
static ssize_t	count_words(char *word_can, t_ptr_tab squote_tab,
								t_ptr_tab dquote_tab, t_ptr_tab redir_tab)
{
	ssize_t	count;
	ssize_t	word_len;

	count = 0;
	while (*word_can)
	{
		word_len = 0;
		word_can += skip_word(word_can, &word_len, redir_tab);
		while (quote_char(*word_can))
		{
			word_can += skip_quoted_word(word_can, squote_tab, &word_len);
			word_can += skip_quoted_word(word_can, dquote_tab, &word_len);
			word_can += skip_word(word_can, &word_len, redir_tab);
		}
		count += word_len > 0;
		while (ft_isspace(*word_can))
			word_can++;
	}
	return (count);
}

static ssize_t	search_word_candidates(char *args, t_mini *msh)
{
	char	*word[2];
	ssize_t	word_len;
	ssize_t	i;

	word[0] = args;
	i = 0;
	while (*word[0] && i < msh->word_tab->count)
	{
		word_len = 0;
		word[0] = skip_redir(word[0], *msh->redir_tab);
		word[1] = word[0];
		word[1] += skip_word(word[1], &word_len, *msh->redir_tab);
		while (quote_char(*word[1]))
		{
			word[1] += skip_quoted_word(word[1], *msh->squote_tab, &word_len);
			word[1] += skip_quoted_word(word[1], *msh->dquote_tab, &word_len);
			word[1] += skip_word(word[1], &word_len, *msh->redir_tab);
		}
		if (word_len > 0)
			save_word(word, msh->word_tab, i++);
		word[0] = word[1];
		while (ft_isspace(*word[0]))
			word[0]++;
	}
	return (i);
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
// 			     start[1]                   end[3]art thou
// TODO: Read on IFS (internal field separator)
// https://www.baeldung.com/linux/ifs-shell-variable
ssize_t	locate_words(char *args, t_mini *msh)
{
	while (*args && ft_isspace(*args))
		args++;
	msh->word_tab->count = count_words(args, *msh->squote_tab,
			*msh->dquote_tab, *msh->redir_tab);
	if (msh->word_tab->count > 0)
	{
		msh->word_tab = ft_taballoc(msh->word_tab, args, sizeof(char *));
		if (!msh->word_tab)
		{
			perror("Error allocating word pointer table");
			return (-1);
		}
		if (search_word_candidates(args, msh) != msh->word_tab->count)
		{
			printf("Error locating words.\n");
			return (-1);
		}
	}
	if (msh->word_tab->count < 0)
		printf("Error locating words.\n");
	return (msh->word_tab->count);
}
