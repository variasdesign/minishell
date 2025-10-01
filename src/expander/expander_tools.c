/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:04:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/09/30 18:13:05 by varias-c         ###   ########.fr       */
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

	var_table = ft_calloc(count + 1, sizeof(char *));
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
				args += var_len;
				i++;
			}
			continue ;
		}
		args++;
	}
	return (var_table);
}

// TODO: Check allowed characters for variable names.
// https://stackoverflow.com/questions/2821043/allowed-characters-in-linux-environment-variable-names:
// Environment variable names used by the utilities in the Shell and Utilities
// volume of IEEE Std 1003.1-2001 consist solely of uppercase letters, digits,
// and the '_' (underscore) from the characters defined in Portable Character Set
// and do not begin with a digit. Other characters may be permitted by an implementation;
// applications shall tolerate the presence of such names.
int	is_variable(char *var_ptr)
{
	int		len;

	len = 0;
	while (var_ptr[len] && (ft_isalnum(var_ptr[len]) || var_ptr[len] == '_'))
		len++;
	return (len);
}
