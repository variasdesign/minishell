/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:55:01 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:40:36 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_unset_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	del_env_var(void *content)
{
	t_env	*env_var;

	if (!content)
		return ;
	env_var = (t_env *)content;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

/// FIX: Invalid unset name should not print anything and return 0
static int	unset_var(char *name, t_list *env_list)
{
	t_node	*current;
	t_env	*env_var;

	if (!is_valid_unset_name(name))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", name);
		return (1);
	}
	current = env_list->head;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (env_var && ft_strncmp(env_var->key, name, ft_strlen(name)) == 0
			&& ft_strlen(env_var->key) == ft_strlen(name))
		{
			ft_lstdel_wrapper(env_list, current, del_env_var);
			return (0);
		}
		current = current->next;
	}
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
