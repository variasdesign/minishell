/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_locate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:22:47 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 18:43:28 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	count_quotes(char *args, char q)
{
	ssize_t	count;
	char	*can;

	count = 0;
	can = ft_strchr(args, q);
	while (can)
	{
		count++;
		can = ft_strchr(can + 1, q);
	}
	return (count);
}

// Look for quote candidates by checking the presence of char q. This will
// be the starting quote. Then, by looking for the next quote, we find
// the ending quote. Since we store the char after the ending quote, we have
// to add one, but only if ft_strchr found something (don't add 1 to NULL).
static ssize_t	search_quote_candidates(t_ptr_tab *quote_tab, char q)
{
	ssize_t	i;

	i = 0;
	if (quote_tab->count > 0)
		quote_tab->start[i] = ft_strchr(quote_tab->orig, q);
	while (i < quote_tab->count && quote_tab->start[i])
	{
		quote_tab->end[i] = ft_strchr(quote_tab->start[i] + 1, q);
		quote_tab->end[i] += quote_tab->end[i] != NULL;
		if (i + 1 < quote_tab->count)
			quote_tab->start[i + 1] = ft_strchr(quote_tab->end[i], q);
		i++;
	}
	return (i);
}

// Locate every (char q) quote and store its start and end in a string table.
// start is a pointer to starting quote, end is a pointer to the next char
// of ending quote. Later, quote validation will be performed to remove
// literal quotes from the table and readjust the count in
// case of odd-numbered quotes.
// Example:	echo My name 'is $USER, hello!'\0
// 			|            |                 |
// 			orig         start[0]          |
// 			                               |
// 			                               end[0]
ssize_t	locate_quotes(char *args, t_ptr_tab *quote_tab, char q)
{
	quote_tab->count = count_quotes(args, q);
	quote_tab->count = quote_tab->count / 2 + quote_tab->count % 2;
	if (quote_tab->count > 0)
	{
		quote_tab = ft_taballoc(quote_tab, args, sizeof(char *));
		if (!quote_tab)
		{
			ft_printf(2, "Error allocating %c quote pointer table: %s\n", q,
				strerror(errno));
			return (-1);
		}
		if (search_quote_candidates(quote_tab, q) != quote_tab->count)
		{
			ft_printf(2, "Error locating %c quotes\n", q);
			return (-1);
		}
	}
	if (quote_tab->count < 0)
		ft_printf(2, "Error locating %c quotes\n", q);
	return (quote_tab->count);
}
