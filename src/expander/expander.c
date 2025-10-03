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
	int		var_len;

	split = split_vars(args, var_table);
	i = 0;
	j = 0;
	while (var_table[i])
	{
		var_len = *(var_table + 1) - *var_table;
		if (ft_strncmp(split[j], var_table[i], var_len))
			j++;
		else
		{
			tmp = split[j];
			// FIX: ft_substr needs to be stored somewhere for later freeing or it will leak
			split[j] = ft_strdup(getenv(ft_substr(var_table[i], 0, var_len)));
			free(tmp);
			var_table += 2;
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
