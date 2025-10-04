/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/04 13:46:22 by varias-c         ###   ########.fr       */
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

// TODO: Research globbing and quoting:
// echo Me llamo $USER y soy $JOB en $COMPANY
// Me llamo varias y soy en <- one space
// echo Me llamo "$USER" y soy "$JOB" en "$COMPANY"
// Me llamo varias y soy  en <- two spaces
char	*expander(char *args)
{
	const char	*orig = args;
	const int	count = count_variables(args);
	char		**var_table;
	char		**split_args;

	if (count > 0)
	{
		var_table = locate_vars(args, count);
		split_args = split_vars(args, var_table);
		args = reassemble_args(args, split_args);
		free((void *)orig);
	}
	return (args);
}
