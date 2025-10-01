/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:04:38 by varias-c          #+#    #+#             */
/*   Updated: 2025/09/30 18:13:05 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable(char *var_ptr)
{
	int		len;

	len = 0;
	// TODO: Check allowed characters for variable names.
	while (!ft_isspace(var_ptr[len]) && var_ptr[len] != '$' && var_ptr[len])
		len++;
	return (len);
}
