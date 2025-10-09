/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_locate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:22:47 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/08 19:45:30 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FIX: Handle interleaved and nested quotes:
// echo "'$USER"' '"$USER'" "'$USER'" '"$USER"'
// Right now quotes are independently counted and located
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

static t_ptr_tab	*search_quotes_candidates(char *args,
											t_ptr_tab *quote_tab, char q)
{
	ssize_t	i;

	quote_tab = ft_taballoc(quote_tab, args, sizeof(char *));
	if (!quote_tab)
	{
		perror(NULL);
		printf("Error allocating %c quote pointer table\n", q);
		return (NULL);
	}
	i = 0;
	quote_tab->start[i] = ft_strchr(quote_tab->orig, q);
	while (i < quote_tab->count && quote_tab->start[i])
	{
		quote_tab->end[i] = ft_strchr(quote_tab->start[i] + 1, q);
		quote_tab->end[i] += quote_tab->end[i] != NULL;
		if (i + 1 < quote_tab->count)
			quote_tab->start[i + 1] = ft_strchr(quote_tab->end[i], q);
		i++;
	}
	return (quote_tab);
}

// Locate every (char q) quote and store its start and end in a string table
// start is a pointer to starting quote, end is a pointer to the next char
// of ending quote.
// Example:	echo My name 'is $USER, hello!'\0
// 			             |                 |
// 			             start[i]          |
// 			                               |
// 			                               end[i]
ssize_t	locate_quotes(char *args, t_ptr_tab *quote_tab, char q)
{
	quote_tab->count = count_quotes(args, q);
	quote_tab->count = quote_tab->count / 2 + quote_tab->count % 2;
	if (quote_tab->count > 0)
	{
		quote_tab = search_quotes_candidates(args, quote_tab, q);
		if (!quote_tab)
			return (-1);
	}
	if (quote_tab->count < 0)
	{
		perror(NULL);
		printf("Error locating %c quotes\n", q);
	}
	return (quote_tab->count);
}
