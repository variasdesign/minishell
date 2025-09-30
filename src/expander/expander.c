/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:21:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/09/30 14:00:14 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_variables(char *args)
{
	size_t count;
	
	count = 0;
	while (args)
	{
		if (args == '$' && !ft_isspace(args + 1))
			count++;
	}

	return (count);
}

static char **allocate_variables(size_t count)
{
	char **vars;

	vars = ft_calloc(count * sizeof(char **));
	return (vars);
}

static char	*expand_variable(char *args, t_node *env)
{
	char *first;
	size_t len;
	char *var_name;


	first = args;
	while (!ft_isspace(*args) || args || *args)
	{
		len++;
		args++;
	}
	var_name = ft_substr(first, 0, len);
	return (get_env(var_name));
}


char	*expander(t_mini *minishell, char *args)
{
	char	*orig;
	char	**vars;
	
	orig = args;
	vars = allocate_variables(count_variables(args));
	if (!vars)	
	{
		free(args);
		printf("Array allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	while (args)
	{
		if (args == '$' && !ft_isspace(args + 1))
		{
			*vars = ft_strdup(expand_variable(args++, minishell->env->head));
		}
		args++;
	}
	free(orig);
	return (args);
}
