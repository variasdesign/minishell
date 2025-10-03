/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:08:58 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/03 18:34:36 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	count_segments(char *args, char **var_table)
{
	int		count;
	int		i;

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

char	**fill_split(char **split, char *args, char **var_table, int count)
{
	int	i;

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
			split[i] = ft_strndup(args, *(var_table + 1) - *var_table);
			args = *(var_table + 1);
			var_table += 2;
		}
		i++;
	}
	if (i < count && !*var_table)
		split[i] = ft_strndup(args, ft_strlen(args));
	return (split);
}

// TODO: custom ft_split + ft_strjoin, ex:
// echo Me llamo $USER$JOB en $COMPANY
// \             \   \\      \  \\
// 0             p1  var_len p2 var_len and so on...
//                     \          \
//                     last_char  last_char
char	**split_vars(char *args, char **var_table)
{
	const int	count = count_segments(args, var_table);
	char		**split;

	split = ft_calloc(count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = fill_split(split, args, var_table, count);
	return (split);
}
