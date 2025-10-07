/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/05 18:33:40 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count the length of the split arguments with expanded vars, then allocate and
// concatenate the split arguments into a single string.
static char	*reassemble_args(char *args, char **split_args)
{
	int		i;
	int		new_len;

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

// TODO: Pass squote_table to split_vars?
// TODO: Free allocated memory in locate funcs
char	*expander(char *args, t_expander *ex)
{
	const char	*orig = args;
	char		**split_args;

	locate_squotes(args, ex->squote_tab);
	if (ex->squote_tab->count < 0)
		return (NULL);
	locate_vars(args, ex);
	if (ex->var_tab->count < 0)
		return (NULL);
	if (ex->var_tab->count > 0)
	{
		split_args = split_vars(ex);
		args = reassemble_args(args, split_args);
		free((void *)orig);
	}
	return (args);
}
