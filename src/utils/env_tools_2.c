/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:17:28 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/06 11:28:14 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*modify_env(t_list *env_list, char *var, char *new_value)
{
	t_env	*content;

	content = get_env(env_list, var);
	if (content)
	{
		free(content->value);
		content->value = ft_strdup(new_value);
		return (env_list);
	}
	return (NULL);
}

t_node	*add_env(t_list *env_list, char *var, char *value)
{
	t_node	*env_node;
	t_env	env_content;

	env_content.key = ft_strdup(var);
	env_content.value = ft_strdup(value);
	env_node = ft_lstnew_node(sizeof(t_env), &env_content);
	ft_lstadd_back(env_list, env_node);
	return (env_node);
}
