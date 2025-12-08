/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2025/12/08 15:07:29 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(char **env)
{
	char	*home;

	home = get_env(env, "HOME");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
	return (home);
}

int	builtin_cd(char **args, char ***env)
{
	char	*path;

	if (args[1] && args[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	
	if (!args[1])
	{
		path = get_home_path(*env);
		if (!path)
			return (1);
	}
	else
		path = args[1];
	
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	
	return (0);
}