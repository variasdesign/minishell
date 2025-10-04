/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:04:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/04 23:20:31 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Unclosed quotes shouldn't be interpreted, but should be notified
// and the prompt restarted. Otherwise, interpret everything as normal.
// Different implementations do either one.
//
// Search for a closing single quote
// and return the length of the quoted segment
static ssize_t	end_quote(char *args)
{
	int	rem_quotes;

	rem_quotes = 0;
	while (args[rem_quotes] && args[rem_quotes] != '\'')
		rem_quotes++;
	if (!args[rem_quotes])
		return (-1);
	return (rem_quotes + 1);
}

// Count variables by checking if they have valid names. Invalid names will
// return var_len = 0. Variables inside single quotes are ignored.
ssize_t	count_variables(char *args)
{
	ssize_t	count;
	ssize_t	var_len;
	ssize_t	rem_quotes;

	count = 0;
	rem_quotes = 0;
	while (*args && *(args + 1))
	{
		var_len = 0;
		if (*args == '\'' && rem_quotes <= 0)
			rem_quotes = end_quote(++args);
		if (*args == '$' && rem_quotes <= 0)
		{
			var_len = is_variable(args + 1);
			count += var_len > 0;
		}
		rem_quotes -= rem_quotes > 0;
		args += 1 + var_len * (var_len > 0);
	}
	return (count);
}

// Locate every variable and store its start and end in a variable table
// Even-numbered pointers are the first char of variable ($),
// odd-numbered pointers are the next char after the last char of variable.
// Example:	echo My name is $USER and I work as $JOB in $COMPANY\0
// 			                |    |              |   |   |       |
// 			                0    1              2   3   4       5
// TODO: Don't store var names inside single quotes
char	**locate_vars(char *args, int count)
{
	char	**var_table;
	ssize_t	var_len;
	int		i;

	var_table = ft_calloc((count * 2) + 1, sizeof(char *));
	var_len = 0;
	i = 0;
	while (*args && *(args + 1))
	{
		if (*args == '$')
		{
			var_len = is_variable(++args);
			if (var_len)
			{
				var_table[i] = args - 1;
				var_table[i + 1] = args + var_len;
				args = var_table[i + 1];
				i += 2;
			}
			continue ;
		}
		args++;
	}
	return (var_table);
}

// https://stackoverflow.com/questions/2821043/
// allowed-characters-in-linux-environment-variable-names
// Environment variable names used by the utilities in the Shell and Utilities
// volume of IEEE Std 1003.1-2001 consist solely of uppercase letters, digits,
// and the '_' (underscore) from the characters defined in Portable Character
// Set and do not begin with a digit. Other characters may be permitted by an
// implementation; applications shall tolerate the presence of such names.
// TODO: Should we avoid reserved keywords also? (e.g. for, while, do, etc)
ssize_t	is_variable(char *var)
{
	int		len;

	len = 0;
	if (!ft_isdigit(var[len]))
		while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
			len++;
	return (len);
}
