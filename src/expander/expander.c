/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/09/30 18:34:36 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**allocate_vars(char *args, size_t count)
{
	char	**vars;

	vars = ft_calloc(count, sizeof(char **));
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
// echo Me llamo $USER y soy $JOB en $COMPANY
// \             \   \\      \  \\
// 0             p1  var_len p2 var_len and so on...
//                     \          \
//                     last_char  last_char
static char	*expand_vars(char *args, t_vars vars)
{
	(void)args;
	(void)vars;
	return (NULL);
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
	t_vars		vars;

	vars.var_table = locate_vars(args, count);
	vars.var_values = obtain_var_values(args, vars.var_table, count);
	args = expand_vars(args, vars);
	free((void *)orig);
	return (args);
}
