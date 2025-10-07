/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:15:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/06 19:39:18 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Return -1 if in_quotes = true?
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

// Locate every single quote and store its start and end in a string table
// start is a pointer to starting quote, end is a pointer to the next char
// of ending quote.
// Example:	echo My name 'is $USER, hello!'\0
// 			             |                 |
// 			             start[i]          |
// 			                               |
// 			                               end[i]
void	locate_squotes(char *args, t_ptr_tab *squote_tab)
{
	ssize_t	i;

	squote_tab->count = count_squotes(args);
	if (squote_tab->count > 0)
	{
		ft_alloptrtab(squote_tab, args, sizeof(char *));
		i = 0;
		squote_tab->start[i] = ft_strchr(squote_tab->orig, '\'');
		while (i < squote_tab->count && squote_tab->start[i])
		{
			squote_tab->end[i] = ft_strchr(squote_tab->start[i] + 1, '\'') + 1;
			squote_tab->start[i] = ft_strchr(squote_tab->end[i], '\'');
			i++;
		}
	}
	if (squote_tab->count < 0)
		perror("Error locating single quotes");
}
