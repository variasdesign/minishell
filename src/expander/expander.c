/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/08 19:34:40 by varias-c         ###   ########.fr       */
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

char	*expander(char *args, t_mini *msh)
{
	const char	*orig = args;
	char		**split_args;

	if (msh->squote_tab->count < 0)
		return (NULL);
	if (msh->var_tab->count < 0)
		return (NULL);
	if (msh->var_tab->count > 0)
	{
		split_args = split_vars(msh);
		args = reassemble_args(args, split_args);
		free((void *)orig);
	}
	return (args);
}
