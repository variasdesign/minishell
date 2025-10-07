/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:22:47 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/07 20:56:00 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FIX: Handle interleaved and nested quotes:
// echo "'$USER"' '"$USER'" "'$USER'" '"$USER"'
// Right now quotes are independently counted and located
static ssize_t	count_dquotes(char *args)
{
	ssize_t	count;
	t_bool	in_quotes;
	char	*quote_can;

	count = 0;
	in_quotes = f;
	quote_can = ft_strchr(args, '\'');
	while (quote_can)
	{
		count += !in_quotes;
		in_quotes = !in_quotes;
		quote_can = ft_strchr(++quote_can, '\"');
	}
	if (in_quotes)
		return (-1);
	return (count);
}

static ssize_t	count_squotes(char *args)
{
	ssize_t	count;
	t_bool	in_quotes;
	char	*quote_can;

	count = 0;
	in_quotes = f;
	quote_can = ft_strchr(args, '\'');
	while (quote_can)
	{
		count += !in_quotes;
		in_quotes = !in_quotes;
		quote_can = ft_strchr(++quote_can, '\'');
	}
	if (in_quotes)
		return (-1);
	return (count);
}

// Locate every single quote and store its start and end in a string table
// start is a pointer to starting quote, end is a pointer to the next char
// of ending quote.
// Example:	echo My name 'is $USER, hello!'\0
// 			             |                 |
// 			             start[i]          |
// 			                               |
// 			                               end[i]
ssize_t	locate_dquotes(char *args, t_ptr_tab *dquote_tab)
{
	ssize_t	i;

	dquote_tab->count = count_squotes(args);
	if (dquote_tab->count > 0)
	{
		dquote_tab = ft_alloptrtab(dquote_tab, args, sizeof(char *));
		if (!dquote_tab)
		{
			perror("Error allocating single quote pointer table");
			return (-1);
		}
		i = 0;
		dquote_tab->start[i] = ft_strchr(dquote_tab->orig, '\'');
		while (i < dquote_tab->count && dquote_tab->start[i])
		{
			dquote_tab->end[i] = ft_strchr(dquote_tab->start[i] + 1, '\"') + 1;
			if (++i < dquote_tab->count)
				dquote_tab->start[i] = ft_strchr(dquote_tab->end[i], '\"');
		}
	}
	if (dquote_tab->count < 0)
		perror("Error locating double quotes");
	return (dquote_tab->count);
}

// Locate every single quote and store its start and end in a string table
// start is a pointer to starting quote, end is a pointer to the next char
// of ending quote.
// Example:	echo My name 'is $USER, hello!'\0
// 			             |                 |
// 			             start[i]          |
// 			                               |
// 			                               end[i]
ssize_t	locate_squotes(char *args, t_ptr_tab *squote_tab)
{
	ssize_t	i;

	squote_tab->count = count_squotes(args);
	if (squote_tab->count > 0)
	{
		squote_tab = ft_alloptrtab(squote_tab, args, sizeof(char *));
		if (!squote_tab)
		{
			perror("Error allocating single quote pointer table");
			return (-1);
		}
		i = 0;
		squote_tab->start[i] = ft_strchr(squote_tab->orig, '\'');
		while (i < squote_tab->count && squote_tab->start[i])
		{
			squote_tab->end[i] = ft_strchr(squote_tab->start[i] + 1, '\'') + 1;
			if (++i < squote_tab->count)
				squote_tab->start[i] = ft_strchr(squote_tab->end[i], '\'');
		}
	}
	if (squote_tab->count < 0)
		perror("Error locating single quotes");
	return (squote_tab->count);
}
