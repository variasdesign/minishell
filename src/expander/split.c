/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:08:58 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/04 22:45:37 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count segments of strings, segregated by variables and non-variables
// Example:	echo My name is $USER and I work as $JOB in $COMPANY
// 			|               |    |              |   |   |
// 			1               2    3              4   5   6
static ssize_t	count_segments(char *args, char **var_table)
{
	ssize_t		count;
	ssize_t		i;

	count = args < var_table[0];
	i = 0;
	while (var_table[i])
	{
		if (i > 0)
			if (var_table[i - 1] != var_table[i])
				count++;
		count++;
		i += 2;
	}
	if (var_table[i - 1] < ft_strlast(args))
		count++;
	return (count);
}

// Obtain var value, checking also for special variable $? (exit status)
static char	*expand_var(char *split, char *args, char **var_table)
{
	const ssize_t	var_len = *(var_table + 1) - *(var_table) - 1;
	const char		first_char = *(*(var_table) + 1);
	char			*tmp_env;

	if (first_char != '?' && var_len > 1)
	{
		tmp_env = ft_strndup(args + 1, var_len);
		split = ft_strdup(getenv(tmp_env));
		free(tmp_env);
	}
	// TODO: Obtain exit status from last executed cmd
	// else
	// 	split = ft_itoa(WEXITSTATUS(status));
	return (split);
}

// Fill the split with its corresponding segmented string. If the segmented
// string is a variable name, obtain its value and expand it.
char	**fill_split(char **split, char *args, char **var_table, int count)
{
	int		i;

	i = 0;
	while (i < count && *var_table)
	{
		if (args < *var_table)
		{
			split[i] = ft_strndup(args, *var_table - args);
			args += *var_table - args;
		}
		else
		{
			split[i] = expand_var(split[i], args, var_table);
			args = *(var_table + 1);
			var_table += 2;
		}
		i++;
	}
	if (i < count && !*var_table)
		split[i] = ft_strndup(args, ft_strlen(args));
	return (split);
}

char	**split_vars(char *args, char **var_table)
{
	const ssize_t	count = count_segments(args, var_table);
	char			**split;

	split = ft_calloc(count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = fill_split(split, args, var_table, count);
	return (split);
}
