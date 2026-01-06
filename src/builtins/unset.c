/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:55:01 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/06 11:54:05 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// FIX: Invalid unset name should not print anything and return 0
static int	unset_var(char *name, t_list *env_list)
{
	t_node	*env_node;

	env_node = get_env_node(env_list, name);
	if (env_node)
		ft_lstdel_wrapper(env_list, env_node, free);
	return (0);
}

int	builtin_unset(char **args, t_list *env_list)
{
	int	i;
	int	exit_status;

	if (!args[1])
		return (0);
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (unset_var(args[i], env_list) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
