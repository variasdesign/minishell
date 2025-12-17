/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/15 20:45:45 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	relocate_variables(t_ptr_tab *var_tab,
								ssize_t j, char *args, char *split_arg)
{
	size_t	split_len;
	size_t	args_len;

	split_len = ft_strlen(split_arg);
	args_len = ft_strlen(args);
	if (split_len > 0)
	{
		var_tab->start[j] = args + args_len - split_len;
		var_tab->end[j] = args + args_len;
		return (j++);
	}
	ft_tabdelone(t, j, var_tab);
	ft_tabdelone(t, j, var_tab);
	return (j);
}

static	ssize_t	relocate_quotes(char *input,
							t_ptr_tab *squote_tab, t_ptr_tab *dquote_tab)
{
	squote_tab = ft_tabfree(&squote_tab, f);
	dquote_tab = ft_tabfree(&dquote_tab, f);
	if (locate_quotes(input, squote_tab, '\'') < 0
		|| locate_quotes(input, dquote_tab, '\"') < 0)
		return (-1);
	if ((squote_tab->count > 0 || dquote_tab->count > 0)
		&& validate_quotes(squote_tab, dquote_tab) < 0)
	{
		squote_tab = ft_tabfree(&squote_tab, f);
		dquote_tab = ft_tabfree(&dquote_tab, f);
		return (-1);
	}
	return (squote_tab->count + dquote_tab->count);
}

// Count the length of the split arguments with expanded vars, then allocate and
// concatenate the split arguments into a single string.
// Also, check if variables were expanded and relocate them
// to avoid unquoted expanded vars becoming redirs
static char	*reassemble_args(char **split_args, t_ptr_tab *var_tab,
							t_bool *expanded_vars)
{
	ssize_t	i;
	ssize_t	j;
	int		new_len;
	char	*args;

	new_len = 0;
	i = 0;
	while (split_args[i])
		new_len += ft_strlen(split_args[i++]);
	args = ft_calloc(new_len + 1, sizeof(char));
	if (!args)
		return (NULL);
	i = -1;
	j = 0;
	while (split_args[++i])
	{
		ft_strlcat(args, split_args[i], new_len + 1);
		if (expanded_vars[i] && j < var_tab->count)
			j = relocate_variables(var_tab, j, args, split_args[i]);
	}
	ft_freematrix((void **)split_args);
	return (args);
}

char	*expander(t_mini *msh)
{
	const char	*orig = msh->input;

	if (locate_quotes(msh->input, msh->squote_tab, '\'') < 0
		|| locate_quotes(msh->input, msh->dquote_tab, '\"') < 0)
		return (NULL);
	if (validate_quotes(msh->squote_tab, msh->dquote_tab) >= 0)
	{
		if (locate_vars(msh->input, msh->var_tab, *msh->squote_tab) > 0
			&& validate_vars(msh->var_tab, msh->dquote_tab) >= 0)
		{
			msh->input = reassemble_args(split_vars(msh), msh->var_tab,
					msh->expanded_vars);
			free((void *)orig);
			msh->squote_tab->orig = msh->input;
			msh->dquote_tab->orig = msh->input;
			msh->var_tab->orig = msh->input;
			if (relocate_quotes(msh->input,
					msh->squote_tab, msh->dquote_tab) < 0)
				return (NULL);
			free(msh->expanded_vars);
		}
		return (msh->input);
	}
	return (NULL);
}
