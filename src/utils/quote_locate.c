/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_locate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:22:47 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/23 18:00:59 by varias-c         ###   ########.fr       */
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

t_ptr_tab	*search_quotes_candidates(t_ptr_tab *quote_tab, char q)
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
	return (quote_tab);
}

// Locate every (char q) quote and store its start and end in a string table
// start is a pointer to starting quote, end is a pointer to the next char
// of ending quote. Later, quote validation will be performed to remove
// literal quotes and readjust the count in case of odd-numbered quotes.
// Example:	echo My name 'is $USER, hello!'\0
// 			             |                 |
// 			             start[0]          |
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
			perror(NULL);
			printf("Error allocating %c quote pointer table\n", q);
			return (-1);
		}
		quote_tab = search_quotes_candidates(quote_tab, q);
	}
	if (quote_tab->count < 0)
	{
		perror(NULL);
		printf("Error locating %c quotes\n", q);
	}
	return (quote_tab->count);
}
