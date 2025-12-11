/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:08:58 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/10 20:01:36 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count segments of strings, segregated by variables and non-variables
// Example:	echo My name is $USER and I work as $JOB in $COMPANY
// 			|               |    |              |   |   |
// 			1               2    3              4   5   6
static ssize_t	count_segments(t_ptr_tab var_tab)
{
	ssize_t		count;
	ssize_t		i;

	count = var_tab.orig < var_tab.start[0];
	i = 0;
	while (i < var_tab.count && var_tab.start[i] && var_tab.end[i])
	{
		count += i > 0 && var_tab.end[i - 1] != var_tab.start[i];
		count++;
		i++;
	}
	count += (char *)var_tab.end[i - 1] < ft_strlast(var_tab.orig);
	return (count);
}

// Obtain var value, checking also for special variable $? (exit status)
// TODO: Research word splitting when empty var names:
// echo My name is $USER and I work as $JOB in $COMPANY
// My name is varias and I work as in <- one space
// echo My name is "$USER" and I work as "$JOB" in "$COMPANY"
// My name is varias and I work as  in <- two spaces
// https://askubuntu.com/questions/850971/bash-variable-expansion-
// behavior-when-using-single-or-double-spaces
static char	*expand_var(t_mini *msh, char *str, t_ptr_tab var_tab, size_t i)
{
	const char		*first_char = var_tab.start[i] + 1;
	const ssize_t	var_len = var_tab.end[i] - (void *)first_char;
	char			*tmp_env;
	char			*env;

	if (var_len > 0)
	{
		if (*first_char != '?')
		{
			tmp_env = ft_strndup(first_char, var_len);
			env = get_env(msh->env, tmp_env)->value;
			if (!env)
				str = ft_strdup("");
			else
				str = ft_strdup(env);
			free(tmp_env);
		}
		else
			str = ft_itoa(g_sig);
	}
	return (str);
}

// Fill the split with its corresponding segmented string. If the segmented
// string is a variable name, obtain its value and expand it.
static char	**fill_split(t_mini *msh, char **split,
						ssize_t count, t_ptr_tab var_tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < count && var_tab.start[j] && var_tab.end[j])
	{
		if (var_tab.read < var_tab.start[j])
		{
			split[i] = ft_strndup(var_tab.read,
					var_tab.start[j] - var_tab.read);
			var_tab.read += var_tab.start[j] - var_tab.read;
		}
		else
		{
			split[i] = expand_var(msh, split[i], var_tab, j);
			var_tab.read = var_tab.end[j];
			j++;
		}
		i++;
	}
	if (i < count && !var_tab.start[j] && !var_tab.end[j])
		split[i] = ft_strndup(var_tab.read,
				ft_strlen(var_tab.read));
	return (split);
}

char	**split_vars(t_mini *msh)
{
	const ssize_t	count = count_segments(*msh->var_tab);
	char			**split;

	split = ft_calloc(count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = fill_split(msh, split, count, *msh->var_tab);
	return (split);
}
