/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2025/12/14 15:52:23 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_exported_vars(t_list *env_list)
{
	t_node	*current;
	t_env	*env_var;

	if (!env_list || !env_list->head)
		return ;
	current = env_list->head;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (env_var && env_var->key && env_var->value)
			printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
		current = current->next;
	}
}

static void	add_new_env_var(t_list *env_list, char *key, char *value)
{
	t_env	*new_var;
	t_node	*new_node;

	new_var = create_env_var(key, value);
	if (new_var)
	{
		new_node = ft_lstnew_node(sizeof(t_env), new_var);
		if (new_node)
			ft_lstadd_back(env_list, new_node);
	}
}

static int	export_var(char *arg, t_list *env_list)
{
	char	*eq_pos;
	char	*key;
	char	*value;
	t_env	*existing;

	if (!is_valid_identifier(arg))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
		return (0);
	key = ft_substr(arg, 0, eq_pos - arg);
	value = ft_strdup(eq_pos + 1);
	if (!key || !value)
		return (1);
	existing = get_env(env_list, key);
	if (existing)
	{
		free(existing->value);
		existing->value = ft_strdup(value);
	}
	else
		add_new_env_var(env_list, key, value);
	free(key);
	free(value);
	return (0);
}

int	builtin_export(char **args, t_list *env_list)
{
	int	i;
	int	exit_status;

	if (!args[1])
	{
		print_exported_vars(env_list);
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (export_var(args[i], env_list) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}