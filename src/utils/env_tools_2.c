/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:17:28 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/05 14:34:51 by varias-c         ###   ########.fr       */
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
	free(env_content.key);
	free(env_content.value);
	ft_lstadd_back(env_list, env_node);
	return (env_node);
}
