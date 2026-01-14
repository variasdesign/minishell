/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:11:24 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/18 14:33:46 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_heredoc_limiter(t_ptr_tab var_tab, ssize_t i)
{
	const size_t	len_until_var = var_tab.start[i] - var_tab.orig;
	size_t			j;

	j = 1;
	while (j <= len_until_var
		&& (ft_isspace(((char *)var_tab.orig)[len_until_var - j])
		|| quote_char(((char *)var_tab.orig)[len_until_var - j])))
		j++;
	if (j <= len_until_var && ((char *)var_tab.orig)[len_until_var - j] == '<')
		j++;
	if (j <= len_until_var && ((char *)var_tab.orig)[len_until_var - j] == '<')
		return (t);
	return (f);
}

// These are special edge cases that invalidate variables, emulating bash
// behavior. These cases are only when is_variable returns 0, which means that
// the variable only contains its $ character. Depending on presence of quotes
// or non-alphanumeric characters, these are invalidated and a literal $ char
// will be printed. Another case is the presence of a variable as a heredoc
// limiter, which would also invalidate it.
ssize_t	validate_vars(t_ptr_tab *var_tab, t_ptr_tab *dquote_tab,
					t_ptr_tab *squote_tab)
{
	ssize_t	i;
	char	*first_char;

	i = 0;
	while (var_tab->start[i])
	{
		first_char = var_tab->start[i] + 1;
		if (check_heredoc_limiter(*var_tab, i)
			|| (!is_variable(var_tab->start[i])
				&& (ft_tabfind(var_tab->start[i], *dquote_tab, f) >= 0
					|| (!ft_isalnum(*(first_char))
						&& ft_tabfind(first_char, *dquote_tab, t) < 0
						&& ft_tabfind(first_char, *squote_tab, t) < 0))))
		{
			var_tab->start[i] = ft_tabdelboth(i, var_tab);
			continue ;
		}
		i++;
	}
	return (var_tab->count);
}
