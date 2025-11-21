/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:11:40 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/21 14:38:34 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **env_list, char *env)
{
	const size_t	len = ft_strlen(env);

	while (*env_list)
	{
		if (!ft_strncmp(*env_list, env, len))
			return (*env_list);
		env_list++;
	}
	return (NULL);
}

char	**init_env(char **envp)
{
	char	**environ;
	size_t	env_count;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	environ = ft_calloc(env_count + 1, sizeof(char *));
	env_count = 0;
	while (envp[env_count])
	{
		environ[env_count] = ft_strdup(envp[env_count]);
		env_count++;
	}
	return (environ);
}
