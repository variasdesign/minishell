/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/03 15:27:25 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**allocate_vars(char *args, size_t count)
{
	char	**vars;

	vars = ft_calloc(count, sizeof(char *));
	if (!vars)
	{
		free(args);
		printf("Array allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	return (vars);
}

static char	**obtain_var_values(char *args, char **var_table, int count)
{
	char			**var_values;
	int				var_len;

	var_values = allocate_vars(args, count);
	var_len = 0;
	while (*var_table)
	{
		var_len = is_variable(*(var_table) + 1);
		*(var_values++) = getenv(ft_substr(*var_table, 1, var_len));
		var_table++;
	}
	return (var_values);
}

// TODO: custom ft_split + ft_strjoin, ex:
// echo Me llamo $USER$JOB en $COMPANY
// \             \   \\      \  \\
// 0             p1  var_len p2 var_len and so on...
//                     \          \
//                     last_char  last_char
static char	**split_vars(char *args, char **var_table)
{
	char	**split;
	int 	count;

	count = args != var_table[0];
}

static char	*expand_vars(char *args, t_vars vars)
{
	int i;
	i = 0;
	while (*args < vars.var_table[i])
	return ();
}

// TODO: Research globbing and quoting:
// echo Me llamo $USER y soy $JOB en $COMPANY
// Me llamo varias y soy en <- one space
// echo Me llamo $USER y soy "$JOB" en "$COMPANY"
// Me llamo varias y soy  en <- two spaces
char	*expander(char *args)
{
	const char	*orig = args;
	const int	count = count_variables(args);
	char		*var_table;

	if (count > 0)
	{
		var_table = locate_vars(args, count);
		args = expand_vars(args, vars);
		free((void *)orig);
	}
	return (args);
}
