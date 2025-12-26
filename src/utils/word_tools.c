/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:48:09 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/03 17:48:57 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_redir(char *str, t_ptr_tab redir_tab)
{
	const ssize_t redir_i = ft_tabfind(str, redir_tab, t);

	if (redir_i >= 0)
		return (redir_tab.end[redir_i]);
	return (str);
}

ssize_t	skip_word(char *str, ssize_t *word_len_ptr, t_ptr_tab redir_tab)
{
	ssize_t	word_len;

	word_len = 0;
	while (str && str[word_len]
		&& !ft_isspace(str[word_len])
		&& !quote_char(str[word_len]))
	{
		if (redir_char(str[word_len])
			&& ft_tabfind(&str[word_len], redir_tab, t) >= 0)
		{
			word_len -= word_len > 0;
			if (word_len > 0)
				break ;
			*word_len_ptr = word_len;
			return (is_redir(&str[word_len]));
		}
		word_len++;
	}
	*word_len_ptr += word_len;
	return (word_len);
}

ssize_t	skip_quoted_word(char *str, t_ptr_tab quote_tab, ssize_t *word_len_ptr)
{
	ssize_t	quote_i;
	ssize_t	word_len;

	word_len = 0;
	if (str && *str)
	{
		quote_i = ft_tabfind(str, quote_tab, t);
		if (quote_i >= 0)
			word_len = (quote_tab.end[quote_i] - quote_tab.start[quote_i]);
		*word_len_ptr += word_len;
	}
	return (word_len);
}

void	save_word(char *word[2], t_ptr_tab *word_tab, ssize_t i)
{
	word_tab->start[i] = word[0];
	word_tab->end[i] = word[1];
}
