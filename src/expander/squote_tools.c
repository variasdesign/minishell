/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:15:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/05 19:18:18 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Return -1 if inquotes = true?
// Depending of handling of unclosed quotes:
// Unclosed quotes shouldn't be interpreted, but should be notified
// and the prompt restarted. Otherwise, interpret everything as normal.
// Different implementations do either one.
static ssize_t	count_squotes(char *args)
{
	ssize_t	count;
	t_bool	in_quotes;
	char	*squote_can;

	count = 0;
	in_quotes = f;
	squote_can = ft_strchr(args, '\'');
	while (squote_can)
	{
		count += !in_quotes;
		in_quotes = !in_quotes;
		squote_can = ft_strchr(++squote_can, '\'');
	}
	if (in_quotes)
		return (-1);
	return (count);
}

// TODO: Binary search to optimize times
// Check if ptr is inside start and end of all instances of single quotes
ssize_t	inside_squotes(char *ptr, t_str_tab sq_t)
{
	ssize_t	i;

	i = 0;
	while (i < sq_t.count && sq_t.start[i] && sq_t.end[i])
	{
		if (ptr > sq_t.start[i] && ptr < sq_t.end[i])
			return (i);
		i++;
	}
	return (-1);
}

// Locate every single quote and store its start and end in a variable table
// start is a pointer to starting quote, end is a pointer to the next char
// of ending quote.
// Example:	echo My name 'is $USER, hello!'\0
// 			             |                 |
// 			             start[i]          |
// 			                               |
// 			                               end[i]
void	locate_squotes(char *args, t_str_tab *sq_t)
{
	ssize_t	i;

	sq_t->count = count_squotes(args);
	if (sq_t->count > 0)
	{
		sq_t->start = ft_calloc(sq_t->count + 1, sizeof(char *));
		sq_t->end = ft_calloc(sq_t->count + 1, sizeof(char *));
		i = 0;
		sq_t->start[i] = ft_strchr(args, '\'');
		while (sq_t->start[i] && i < sq_t->count)
		{
			sq_t->end[i] = ft_strchr(sq_t->start[i] + 1, '\'') + 1;
			i++;
			sq_t->start[i] = ft_strchr(sq_t->end[i - 1], '\'');
		}
	}
}
