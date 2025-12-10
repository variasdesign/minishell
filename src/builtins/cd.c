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

static char	*change_pwd(char ***env)
{
	ssize_t	pwd_var;
	char	*new_cwd;

	pwd_var = get_env_index(*env, "PWD");
	if (pwd_var > 0)
	{
		free((*env)[pwd_var]);
		new_cwd = getcwd(NULL, 0);
		(*env)[pwd_var] = ft_strjoin("PWD=", new_cwd);
		free(new_cwd);
		return ((*env)[pwd_var]);
	}
	printf("minishell: cd: PWD not found\n");
	return (NULL);
}

int	builtin_cd(char **args, char ***env)
{
	char	*path;

	if (ft_arrlen((void **)args) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!args[1])
	{
		path = get_home_path(*env);
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
	if (!change_pwd(env))
		return (1);
	return (0);
}
