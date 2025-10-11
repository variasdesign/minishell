/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:22:03 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/11 16:45:50 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	find_and_del_quotes(t_ptr_tab *lead_tab, t_ptr_tab *second_tab)
{
	ssize_t	i;
	ssize_t	start_i;
	ssize_t	end_i;

	i = 0;
	while (second_tab->start[i])
	{
		start_i = ft_tabfind(second_tab->start[i], *lead_tab);
		end_i = ft_tabfind(second_tab->end[i], *lead_tab);
		if (start_i >= 0)
			second_tab->start[i] = ft_tabdelone(f, i, second_tab);
		else if (end_i >= 0
			&& ft_tabfind(lead_tab->start[end_i], *second_tab) < 0)
			second_tab->end[i] = ft_tabdelone(t, i, second_tab);
		else
			i++;
	}
	return (lead_tab->count + second_tab->count);
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
	const t_bool	lead_quote = squote_tab->start[0] > dquote_tab->start[0];
	ssize_t			new_count;

	new_count = squote_tab->count + dquote_tab->count;
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
	return (new_count);
}
