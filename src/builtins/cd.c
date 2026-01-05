/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2026/01/05 14:38:19 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_list *env_list)
{
	char	*home;

	home = get_env(env_list, "HOME")->value;
	if (!home)
	{
		ft_printf(2, E_SHELL_PERROR, "cd", "HOME not set");
		return (NULL);
	}
	return (home);
}

static char	*change_pwd(t_list *env_list)
{
	char	*new_cwd;
	t_env	*old_pwd;
	t_env	*pwd;

	new_cwd = getcwd(NULL, 0);
	old_pwd = get_env(env_list, "OLDPWD");
	pwd = get_env(env_list, "PWD");
	if (pwd)
	{
		if (old_pwd)
			modify_env(env_list, "OLDPWD", pwd->value);
		else
			add_env(env_list, "OLDPWD", pwd->value);
	}
	env_list = modify_env(env_list, "PWD", new_cwd);
	free(new_cwd);
	if (!env_list)
	{
		ft_printf(2, E_SHELL_PERROR, "cd", "PWD not found");
		return (NULL);
	}
	return (get_env(env_list, "PWD")->value);
}

int	builtin_cd(char **args, t_list *env_list)
{
	char	*path;

	if (ft_arrlen((void **)args) > 2)
	{
		ft_printf(2, E_SHELL_PERROR, "cd", "too many arguments");
		return (2);
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
		ft_printf(2, "minishell: cd: %s: %s\n", path, "No such file or directory");
		return (1);
	}
	if (!change_pwd(env_list))
		return (1);
	return (0);
}
