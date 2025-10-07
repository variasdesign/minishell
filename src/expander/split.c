/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:08:58 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/07 20:38:15 by varias-c         ###   ########.fr       */
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
static char	*expand_var(char *str, t_ptr_tab var_tab,
					size_t i, t_ptr_tab dquote_tab)
{
	const ssize_t	var_len = var_tab.end[i] - var_tab.start[i] - 1;
	const char		*first_char = var_tab.start[i] + 1;
	char			*tmp_env;
	char			*env;

	if (*first_char != '?' && var_len > 1)
	{
		tmp_env = ft_strndup(var_tab.start[i] + 1, var_len);
		env = getenv(tmp_env);
		if (!env && ft_inptrtab(var_tab.start[i], dquote_tab))
			str = ft_strdup(" ");
		else
			str = ft_strdup(env);
		free(tmp_env);
	}
	// TODO: Obtain exit status from last executed cmd
	// else
	// 	split = ft_itoa(WEXITSTATUS(status));
	return (str);
}

// Fill the split with its corresponding segmented string. If the segmented
// string is a variable name, obtain its value and expand it.
// TODO: Research double quoting when empty var names:
// echo Me llamo $USER y soy $JOB en $COMPANY
// Me llamo varias y soy en <- one space
// echo Me llamo "$USER" y soy "$JOB" en "$COMPANY"
// Me llamo varias y soy  en <- two spaces
// TODO: Remove quotes before filling split
char	**fill_split(char **split, ssize_t count, t_mini *msh)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < count && msh->var_tab->start[j] && msh->var_tab->end[j])
	{
		if (msh->var_tab->read < msh->var_tab->start[j])
		{
			split[i] = ft_strndup(msh->var_tab->read,
					msh->var_tab->start[i] - msh->var_tab->read);
			msh->var_tab->read += msh->var_tab->start[j] - msh->var_tab->read;
		}
		else
		{
			split[i] = expand_var(split[i], *msh->var_tab, j, *msh->dquote_tab);
			msh->var_tab->read = msh->var_tab->end[j];
			j++;
		}
		i++;
	}
	if (i < count && !msh->var_tab->start[j] && !msh->var_tab->end[j])
		split[i] = ft_strndup(msh->var_tab->read,
				ft_strlen(msh->var_tab->read));
	return (split);
}

char	**split_vars(t_mini *msh)
{
	const ssize_t	count = count_segments(*msh->var_tab);
	char			**split;

	split = ft_calloc(count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = fill_split(split, count, msh);
	return (split);
}
