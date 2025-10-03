/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:04:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/03 18:31:17 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_variables(char *args)
{
	size_t	count;
	int		var_len;

	count = 0;
	var_len = 0;
	while (*args && *(args + 1))
	{
		if (*args == '$')
		{
			var_len = is_variable(++args);
			if (var_len)
			{
				count++;
				args += var_len;
				continue ;
			}
		}
		args++;
	}
	return (count);
}

char	**locate_vars(char *args, int count)
{
	char	**var_table;
	int		var_len;
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

// https://stackoverflow.com/questions/2821043/allowed-characters-in-linux-environment-variable-names:
// Environment variable names used by the utilities in the Shell and Utilities
// volume of IEEE Std 1003.1-2001 consist solely of uppercase letters, digits,
// and the '_' (underscore) from the characters defined in Portable Character Set
// and do not begin with a digit. Other characters may be permitted by an implementation;
// applications shall tolerate the presence of such names.
// TODO: Should we avoid reserved keywords also? (e.g. for, while, do, etc)
int	is_variable(char *var_ptr)
{
	int		len;

	len = 0;
	if (!ft_isdigit(var_ptr[len]))
		while (var_ptr[len] && (ft_isalnum(var_ptr[len]) || var_ptr[len] == '_'))
			len++;
	return (len);
}
