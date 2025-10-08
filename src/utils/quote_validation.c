/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:22:03 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/08 20:45:20 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FIX: ft_tabdelone is not working correctly (see ft_ptrtab from libft)
ssize_t	find_and_del_quotes(t_ptr_tab *lead_tab, t_ptr_tab *second_tab)
{
	ssize_t			i;

	i = 0;
	while (second_tab->start[i])
	{
		if (ft_tabfind(second_tab->start[i], *lead_tab) >= 0)
			second_tab->start[i] = ft_tabdelone(f, i, second_tab);
		else if (ft_tabfind(second_tab->end[i], *lead_tab) >= 0)
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
ssize_t	validate_quotes(t_ptr_tab *squote_tab, t_ptr_tab *dquote_tab)
{
	const t_bool	lead_quote = squote_tab->start[0] > dquote_tab->start[0];
	ssize_t			new_count;

	new_count = squote_tab->count + dquote_tab->count;
	if (!lead_quote)
		new_count = find_and_del_quotes(new_count, squote_tab, dquote_tab);
	else
		new_count = find_and_del_quotes(new_count, dquote_tab, squote_tab);
	return (new_count);
}
