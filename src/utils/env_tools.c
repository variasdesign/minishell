/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:11:40 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/05 14:26:52 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**reassemble_env(t_list *env_list)
{
	char	**env_matrix;
	char	*tmp;
	ssize_t	i;

	env_matrix = ft_calloc(env_list->count + 1, sizeof(char *));
	i = 0;
	while (i < env_list->count)
	{
		env_matrix[i] = ft_strdup(get_env_pos(env_list, i)->key);
		tmp = ft_strjoin(env_matrix[i], "=");
		free(env_matrix[i]);
		env_matrix[i] = tmp;
		tmp = ft_strjoin(env_matrix[i], get_env_pos(env_list, i)->value);
		free(env_matrix[i]);
		env_matrix[i] = tmp;
		i++;
	}
	return (env_matrix);
}

t_env	*get_env_pos(t_list *env_list, ssize_t pos)
{
	t_node	*env_node;

	env_node = ft_lstfind_node(env_list, pos);
	if (env_node)
		return (env_node->content);
	return (NULL);
}

t_env	*get_env(t_list *env_list, char *var)
{
	const size_t	var_len = ft_strlen(var);
	t_node			*env_node;
	t_env			*env;
	size_t			key_len;

	env_node = env_list->head;
	while (env_node && var && *var)
	{
		env = env_node->content;
		key_len = ft_strlen(env->key);
		if (key_len == var_len && !ft_strncmp(env->key, var, var_len))
			return (env);
		env_node = env_node->next;
	}
	return (NULL);
}

ssize_t	get_env_index(t_list *env_list, char *var)
{
	const size_t	len = ft_strlen(var);
	t_node			*env;
	t_env			*content;
	ssize_t			i;

	i = 0;
	env = env_list->head;
	while (env)
	{
		content = env->content;
		if (!ft_strncmp(content->key, var, len))
			return (i);
		env = env->next;
		i++;
	}
	return (-1);
}
