/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:04:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/08 19:34:31 by varias-c         ###   ########.fr       */
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
		squote_i = ft_tabfind(var_can, squote_tab);
		if (squote_i < 0)
		{
			var_len = is_variable(var_can);
			count += var_len > 0;
			var_can = ft_strchr(++var_can + var_len, '$');
		}
		else
			var_can = ft_strchr(squote_tab.end[squote_i], '$');
	}
	return (count);
}

void	search_var_candidate(t_ptr_tab *var_tab, t_ptr_tab squote_tab)
{
	ssize_t	var_len;
	ssize_t	squote_i;
	char	*var_can;
	ssize_t	i;

	var_can = ft_strchr(var_tab->orig, '$');
	var_len = 0;
	squote_i = -1;
	i = -1;
	while (++i < var_tab->count && var_can)
	{
		squote_i = ft_tabfind(var_can, squote_tab);
		if (squote_i < 0)
		{
			var_len = is_variable(var_can);
			if (var_len)
			{
				var_tab->start[i] = var_can;
				var_tab->end[i] = ++var_can + var_len;
			}
			var_can = ft_strchr(var_can, '$');
		}
		else
			var_can = ft_strchr(squote_tab.end[squote_i], '$');
	}
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
			perror("Error allocating variable pointer table");
			return (-1);
		}
		search_var_candidate(var_tab, squote_tab);
	}
	if (var_tab->count < 0)
		perror("Error locating variables");
	return (var_tab->count);
}
