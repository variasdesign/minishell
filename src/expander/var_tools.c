/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:04:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/05 19:18:00 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// https://stackoverflow.com/questions/2821043/
// allowed-characters-in-linux-environment-variable-names
// Environment variable names used by the utilities in the Shell and Utilities
// volume of IEEE Std 1003.1-2001 consist solely of uppercase letters, digits,
// and the '_' (underscore) from the characters defined in Portable Character
// Set and do not begin with a digit. Other characters may be permitted by an
// implementation; applications shall tolerate the presence of such names.
// TODO: Should we avoid reserved keywords also? (e.g. for, while, do, etc)
static ssize_t	is_variable(char *var)
{
	int		len;

	len = 0;
	if (!ft_isdigit((++var)[len]))
		while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
			len++;
	return (len);
}

// Count variables by checking if they have valid names. Invalid names will
// return var_len = 0. Variables inside single quotes are ignored.
static ssize_t	count_variables(char *args, t_str_tab sq_t)
{
	ssize_t	count;
	ssize_t	var_len;
	ssize_t	quote_i;
	char	*var_can;

	count = 0;
	var_can = ft_strchr(args, '$');
	while (var_can)
	{
		quote_i = inside_squotes(var_can, sq_t);
		if (quote_i < 0)
		{
			var_len = is_variable(var_can);
			count += var_len > 0;
			var_can = ft_strchr(++var_can + var_len, '$');
		}
		else
			var_can = ft_strchr(sq_t.end[quote_i], '$');
	}
	return (count);
}

void	search_var_candidate(char *args, t_str_tab *var_t, t_str_tab sq_t)
{
	ssize_t	var_len;
	ssize_t	quote_i;
	char	*var_can;
	ssize_t	i;

	var_can = ft_strchr(args, '$');
	var_len = 0;
	quote_i = -1;
	i = -1;
	while (++i < var_t->count && var_can)
	{
		quote_i = inside_squotes(var_can, sq_t);
		if (quote_i < 0)
		{
			var_len = is_variable(var_can);
			if (var_len)
			{
				var_t->start[i] = var_can;
				var_t->end[i] = ++var_can + var_len;
			}
			var_can = ft_strchr(var_can, '$');
		}
		else
			var_can = ft_strchr(sq_t.end[quote_i], '$');
	}
}
// Locate every variable and store its start and end in a variable table
// i is the index of the variable, start is a pointer to first char,
// end is a pointer to next char of last.
// Example:	echo My name is $USER, hello!
// 			                |    |
// 			                start[i]
// 			                     |
// 			                     end[i]
// TODO: Don't store var names inside single quotes
void	locate_vars(char *args, t_str_tab *var_t, t_str_tab sq_t)
{
	var_t->count = count_variables(args, sq_t);
	var_t->start = ft_calloc(var_t->count + 1, sizeof(char *));
	var_t->end = ft_calloc(var_t->count + 1, sizeof(char *));
	search_var_candidate(args, var_t, sq_t);
}
