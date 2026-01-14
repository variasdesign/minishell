/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2026/01/12 18:40:36 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **args, t_list *env_list)
{
	t_node	*current;
	t_env	*env_var;

	(void)args;
	if (!env_list || !env_list->head)
		return (1);
	current = env_list->head;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (env_var && env_var->key && env_var->value)
			ft_printf(1, "%s=%s\n", env_var->key, env_var->value);
		current = current->next;
	}
	return (0);
}
