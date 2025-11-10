/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/13 13:53:36 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count the length of the split arguments with expanded vars, then allocate and
// concatenate the split arguments into a single string.
static char	*reassemble_args(char **split_args)
{
	int		i;
	int		new_len;
	char	*args;

	new_len = 0;
	i = 0;
	while (split_args[i])
		new_len += ft_strlen(split_args[i++]);
	args = ft_calloc(new_len + 1, sizeof(char));
	if (!args)
		return (NULL);
	i = 0;
	while (split_args[i])
		ft_strlcat(args, split_args[i++], new_len + 1);
	ft_freematrix((void **)split_args);
	return (args);
}

char	*expander(char *args, t_ptr_tab *squote_tab,
					t_ptr_tab *dquote_tab, t_ptr_tab *var_tab)
{
	const char	*orig = args;

	if (locate_quotes(args, squote_tab, '\'') < 0
		|| locate_quotes(args, dquote_tab, '\"') < 0)
		return (NULL);
	if ((squote_tab->count > 0 && dquote_tab->count > 0)
		&& validate_quotes(squote_tab, dquote_tab) < 0)
	{
		squote_tab = ft_tabfree(&squote_tab);
		dquote_tab = ft_tabfree(&dquote_tab);
		return (NULL);
	}
	if (locate_vars(args, var_tab, *squote_tab) < 0)
		return (NULL);
	if (var_tab->count > 0)
	{
		args = reassemble_args(split_vars(var_tab));
		free((void *)orig);
		squote_tab->orig = args;
		dquote_tab->orig = args;
	}
	return (args);
}
