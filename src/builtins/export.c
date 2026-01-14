/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2026/01/12 19:08:04 by ttonchak         ###   ########.fr       */
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

/// FIX: Exported variables are not sorted like bash does
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
			ft_printf(1, "declare -x %s=\"%s\"\n",
				env_var->key, env_var->value);
		current = current->next;
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
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", arg);
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
		modify_env(env_list, existing->key, value);
	else
		add_env(env_list, key, value);
	free(key);
	free(value);
	return (0);
}

int	builtin_export(char **args, t_list *env_list)
{
	int	i;

	if (!args[1])
	{
		print_exported_vars(env_list);
		return (0);
	}
	g_sig = 0;
	i = 1;
	while (args[i])
	{
		if (export_var(args[i], env_list))
			g_sig = 1;
		i++;
	}
	return (g_sig);
}
