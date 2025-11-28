/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:27:12 by varias-c         ###   ########.fr       */
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

char	*expander(char *args, t_mini *msh)
{
	const char	*orig = args;

	if (locate_quotes(args, msh->squote_tab, '\'') < 0
		|| locate_quotes(args, msh->dquote_tab, '\"') < 0)
		return (NULL);
	if ((msh->squote_tab->count > 0 && msh->dquote_tab->count > 0)
		&& validate_quotes(msh->squote_tab, msh->dquote_tab) < 0)
	{
		msh->squote_tab = ft_tabfree(&msh->squote_tab, f);
		msh->dquote_tab = ft_tabfree(&msh->dquote_tab, f);
		return (NULL);
	}
	if (locate_vars(args, msh->var_tab, *msh->squote_tab) < 0)
		return (NULL);
	if (msh->var_tab->count > 0)
	{
		args = reassemble_args(split_vars(msh));
		free((void *)orig);
		msh->squote_tab->orig = args;
		msh->dquote_tab->orig = args;
	}
	return (args);
}
