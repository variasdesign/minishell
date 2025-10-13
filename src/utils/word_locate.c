/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_locate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:54:03 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/13 14:05:08 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count words by checking if they are valid. Invalid words will
// return word_len = 0. Words inside single or double quotes are counted as one.
static ssize_t	count_words(char *args, t_ptr_tab squote_tab,
								t_ptr_tab dquote_tab)
{
	ssize_t	count;
	ssize_t	word_len;
	ssize_t	squote_i;
	ssize_t	dquote_i;
	char	*word_can;

	count = 0;
	return (count);
}

static void	search_word_candidate(t_ptr_tab *word_tab, t_ptr_tab squote_tab,
									t_ptr_tab dquote_tab)
{
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
		search_word_candidate(msh->word_tab, *msh->squote_tab,
			*msh->dquote_tab);
	}
	if (msh->word_tab->count < 0)
		printf("Error locating words.\n");
	return (msh->word_tab->count);
}
