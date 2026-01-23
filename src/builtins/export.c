/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2026/01/20 20:10:38 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (f);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (f);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (f);
		i++;
	}
	return (t);
}

static void	print_exported_vars(t_list *sorted_env)
{
	t_node	*current;
	t_env	*env_var;

	current = sorted_env->head;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (env_var && env_var->key && env_var->value)
			ft_printf(1, "declare -x %s=\"%s\"\n",
				env_var->key, env_var->value);
		else if (env_var && env_var->key)
			ft_printf(1, "declare -x %s\n", env_var->key);
		current = current->next;
	}
}

static int	export_var(char *arg, t_list *env_list, t_list *export_list)
{
	char	*eq_pos;
	char	*key;
	char	*value;
	t_env	*existing;

	if (!is_valid_identifier(arg))
		return (ft_printf(2, E_EXPORT_IDENT, arg), 1);
	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
		return (!add_env(export_list, arg, NULL));
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

static void	add_exported_to_env(t_list *env_list, t_list *sorted_env,
							t_list *export_list)
{
	t_node	*node;
	t_env	*env;

	node = env_list->head;
	while (node)
	{
		env = node->content;
		if (env)
			add_env(sorted_env, env->key, env->value);
		node = node->next;
	}
	node = export_list->head;
	while (node)
	{
		env = node->content;
		if (env)
			add_env(sorted_env, env->key, env->value);
		node = node->next;
	}
}

int	builtin_export(char **args, t_list *env_list, t_list *export_list)
{
	t_list	*sorted_env;
	int		i;

	if (!args[1])
	{
		if (!env_list || !env_list->head)
			return (1);
		sorted_env = ft_lstnew_list(env_list->data_size);
		add_exported_to_env(env_list, sorted_env, export_list);
		sort_exported_vars(sorted_env);
		if (!sorted_env || !sorted_env->head)
			return (1);
		print_exported_vars(sorted_env);
		ft_lstdel_list(sorted_env, free_env_list);
		return (0);
	}
	i = 1;
	while (args[i])
		if (export_var(args[i++], env_list, export_list))
			return (1);
	return (0);
}
