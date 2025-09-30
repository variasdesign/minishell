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

static size_t	count_variables(char *args)
{
	size_t	count;

	count = 0;
	while (*args)
	{
		if (*args == '$' && !ft_isspace(*(args + 1)))
			count++;
		args++;
	}
	return (count);
}

static char	**allocate_variables(char *args, size_t count)
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

char	*expander(char *args)
{
	const ssize_t	count = count_variables(args);
	const char		*orig = args;
	char			**vars;
	int				var_len;

	vars = allocate_variables(args, count);
	while (*args && *args + 1)
	{
		if (*args == '$')
		{
			var_len = is_variable(++args);
			if (var_len)
			{
				*vars++ = getenv(ft_substr(args, 0, var_len));
				args += var_len;
				continue ;
			}
		}
		else
			args++;
	}
	free((void *)orig);
	return (args);
}
