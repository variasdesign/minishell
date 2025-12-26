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

// FIX: Expand criteria for var invalidation:
// echo $/ $/
// echo "$/ $/"
// echo $/"$/"
// All these fail to invalidate
ssize_t	validate_vars(t_ptr_tab *var_tab, t_ptr_tab *dquote_tab)
{
	ssize_t	i;
	ssize_t	var_len;

	i = 0;
	while (var_tab->start[i])
	{
		var_len = is_variable(var_tab->start[i]);
		if (!var_len && ft_tabfind(var_tab->start[i], *dquote_tab, f) >= 0)
		{
			var_tab->start[i] = ft_tabdelboth(i, var_tab);
		}
		i++;
	}
	return (var_tab->count);
}
