/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/03 18:30:25 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_vars(char *args, char **var_table)
{
	char	**split;
	char	*tmp;
	int		i;
	int		j;

	split = split_vars(args, var_table);
	i = 0;
	j = 0;
	while (var_table[i])
	{
		if (ft_strncmp(split[j], var_table[i], ft_strlen(var_table[i])))
			j++;
		else
		{
			tmp = split[j];
			split[j] = ft_strdup(getenv(var_table[i]));
			free(tmp);
		}
	}
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

	if (count > 0)
	{
		var_table = locate_vars(args, count);
		args = expand_vars(args, var_table);
		free((void *)orig);
	}
	return (args);
}
