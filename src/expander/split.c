/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:08:58 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/05 19:37:47 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count segments of strings, segregated by variables and non-variables
// Example:	echo My name is $USER and I work as $JOB in $COMPANY
// 			|               |    |              |   |   |
// 			1               2    3              4   5   6
static ssize_t	count_segments(char *args, t_str_tab var_t)
{
	ssize_t		count;
	ssize_t		i;

	count = args < var_t.start[0];
	i = 0;
	while (i < var_t.count && var_t.start[i] && var_t.end[i])
	{
		count += i > 0 && var_t.end[i - 1] != var_t.start[i];
		count++;
		i++;
	}
	if (var_t.end[i - 1] < ft_strlast(args))
		count++;
	return (count);
}

// Obtain var value, checking also for special variable $? (exit status)
static char	*expand_var(char *split, char *args, t_str_tab var_t, size_t index)
{
	const ssize_t	var_len = var_t.end[index] - var_t.start[index] - 1;
	const char		*first_char = var_t.start[index] + 1;
	char			*tmp_env;

	if (*first_char != '?' && var_len > 1)
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
// TODO: Research double quoting when empty var names:
// echo Me llamo $USER y soy $JOB en $COMPANY
// Me llamo varias y soy en <- one space
// echo Me llamo "$USER" y soy "$JOB" en "$COMPANY"
// Me llamo varias y soy  en <- two spaces
// TODO: Remove quotes before filling split
char	**fill_split(char **split, char *args, t_str_tab var_t, ssize_t count)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < count && var_t.start[j] && *var_t.end[j])
	{
		if (args < var_t.start[j])
		{
			split[i] = ft_strndup(args, var_t.start[j] - args);
			args += var_t.start[j] - args;
		}
		else
		{
			split[i] = expand_var(split[i], args, var_t, j);
			args = var_t.end[j];
			j++;
		}
		i++;
	}
	if (i < count && !var_t.start[j] && !var_t.end[j])
		split[i] = ft_strndup(args, ft_strlen(args));
	return (split);
}

char	**split_vars(char *args, t_str_tab var_table)
{
	const ssize_t	count = count_segments(args, var_table);
	char			**split;

	split = ft_calloc(count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = fill_split(split, args, var_table, count);
	return (split);
}
