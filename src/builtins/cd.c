/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2025/12/10 20:15:09 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_list *env_list)
{
	char	*home;

	home = get_env(env_list, "HOME")->value;
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
	return (home);
}

static char	*change_pwd(t_list *env_list)
{
	char	*new_cwd;

	new_cwd = getcwd(NULL, 0);
	env_list = modify_env(env_list, "PWD", new_cwd);
	free(new_cwd);
	if (!env_list)
	{
		printf("minishell: cd: PWD not found\n");
		return (NULL);
	}
	return (get_env(env_list, "PWD")->value);
}

int	builtin_cd(char **args, t_list *env_list)
{
	char	*path;

	if (ft_arrlen((void **)args) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!args[1])
	{
		path = get_home_path(env_list);
		if (!path)
			return (0);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (!change_pwd(env_list))
		return (1);
	return (0);
}
