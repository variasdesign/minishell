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

char	*expander(t_mini *minishell, char *args)
{
	char	*tmp;

	tmp = args;
	args = expand_variables(tmp);
	free(tmp);
	return (args);
}
