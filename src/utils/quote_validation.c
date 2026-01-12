/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:22:03 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 18:43:43 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_char(char c)
{
	return (c == '\"' || c == '\'');
}

ssize_t	find_and_del_quotes(t_ptr_tab *lead_tab, t_ptr_tab *second_tab)
{
	ssize_t	i;
	ssize_t	start_i;
	ssize_t	end_i;

	i = 0;
	while (second_tab->start[i])
	{
		start_i = ft_tabfind(second_tab->start[i], *lead_tab, f);
		end_i = ft_tabfind(second_tab->end[i], *lead_tab, f);
		if (start_i >= 0)
			second_tab->start[i] = ft_tabdelone(f, i, second_tab);
		else if (end_i >= 0
			&& ft_tabfind(lead_tab->start[end_i], *second_tab, f) < 0)
			second_tab->end[i] = ft_tabdelone(t, i, second_tab);
		else
			i++;
	}
	return (lead_tab->count + second_tab->count);
}

static t_bool	check_quotes_parity(t_ptr_tab quote_tab)
{
	if (quote_tab.count > 0)
	{
		if (!quote_tab.end[quote_tab.count - 1])
		{
			ft_printf(2, E_QUOTE_PARITY, *(char *)quote_tab.start[0]);
			return (f);
		}
	}
	return (t);
}

// Quote validation:
// 1. Determine lead quote type by looking at leftmost char
// 2. Iterate over second quote type pointer table and search
// for ocurrences in ranges of lead quote type. If found, invalidate quote
// by replacing it with posterior quotes in the table (if any).
// 3. Reverse search to find occurrences of lead quotes in
// second quote table.
ssize_t	validate_quotes(t_ptr_tab *squote_tab, t_ptr_tab *dquote_tab)
{
	t_bool	lead_quote;
	ssize_t	new_count;

	new_count = squote_tab->count + dquote_tab->count;
	if (squote_tab->count > 0 && dquote_tab->count > 0)
	{
		lead_quote = squote_tab->start[0] > dquote_tab->start[0];
		if (!lead_quote)
		{
			new_count = find_and_del_quotes(squote_tab, dquote_tab);
			new_count = find_and_del_quotes(dquote_tab, squote_tab);
		}
		else
		{
			new_count = find_and_del_quotes(dquote_tab, squote_tab);
			new_count = find_and_del_quotes(squote_tab, dquote_tab);
		}
	}
	if (!check_quotes_parity(*squote_tab) || !check_quotes_parity(*dquote_tab))
		return (-1);
	return (new_count);
}
