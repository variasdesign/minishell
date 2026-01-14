/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:04:38 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 18:45:03 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (var)
	{
		if (!ft_isdigit((++var)[len]))
		{
			if (var[len] == '?')
				return (++len);
			while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
				len++;
			return (len);
		}
	}
	return (-1);
}

// Count variables by checking if they have valid names. Invalid names will
// return var_len = -1. Variables inside single quotes are ignored.
static ssize_t	count_variables(char *args, t_ptr_tab squote_tab)
{
	ssize_t	count;
	ssize_t	var_len;
	ssize_t	squote_i;
	char	*var_can;

	count = 0;
	var_can = ft_strchr(args, '$');
	while (var_can)
	{
		squote_i = ft_tabfind(var_can, squote_tab, f);
		if (squote_i < 0)
		{
			var_len = is_variable(var_can);
			count += var_len >= 0;
			var_can = ft_strchr(++var_can + var_len, '$');
		}
		else
			var_can = ft_strchr(squote_tab.end[squote_i], '$');
	}
	return (count);
}

static ssize_t	save_var(t_ptr_tab *var_tab, ssize_t i,
						char *var_can, ssize_t var_len)
{
	if (var_len >= 0)
	{
		var_tab->start[i] = var_can;
		var_tab->end[i++] = var_can + var_len + 1;
	}
	return (i);
}

// Look for $ characters to find variable candidates, then check its preliminar
// validity with is_variable. Later, we will perform secondary validation for
// special edge cases that invalidate variables.
static ssize_t	search_var_candidates(t_ptr_tab *var_tab, t_ptr_tab squote_tab)
{
	ssize_t	squote_i;
	char	*var_can;
	ssize_t	i;

	var_can = ft_strchr(var_tab->orig, '$');
	squote_i = -1;
	i = 0;
	while (i < var_tab->count && var_can)
	{
		squote_i = ft_tabfind(var_can, squote_tab, f);
		if (squote_i < 0)
		{
			i = save_var(var_tab, i, var_can, is_variable(var_can));
			var_can = ft_strchr(++var_can, '$');
		}
		else
			var_can = ft_strchr(squote_tab.end[squote_i], '$');
	}
	return (i);
}

// Locate every variable and store its start and end in a pointer table.
// start is a pointer to first char, end is a pointer to next char of last.
// Example:	echo My name is $USER, hello!
// 			|               |    |
// 			orig            start[0]
// 			                     |
// 			                     end[0]
ssize_t	locate_vars(char *args, t_ptr_tab *var_tab, t_ptr_tab squote_tab)
{
	var_tab->count = count_variables(args, squote_tab);
	if (var_tab->count > 0)
	{
		var_tab = ft_taballoc(var_tab, args, sizeof(char *));
		if (!var_tab)
		{
			ft_printf(2, "Error allocating variable pointer table: %s\n",
				strerror(errno));
			return (-1);
		}
		if (search_var_candidates(var_tab, squote_tab) != var_tab->count)
		{
			ft_printf(2, "Error locating variables\n");
			return (-1);
		}
	}
	if (var_tab->count < 0)
		ft_printf(2, "Error locating variables\n");
	return (var_tab->count);
}
