/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:25:35 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 19:44:47 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*direct_path(char *exec)
{
	DIR	*dir;

	dir = opendir(exec);
	if (!dir)
	{
		if (!access(exec, R_OK | X_OK))
			return (ft_strdup(exec));
		g_sig = 127;
		ft_printf(2, E_SHELL_PERROR, exec, strerror(errno));
	}
	else
	{
		g_sig = 126;
		ft_printf(2, E_SHELL_PERROR, exec, "Is a directory");
		closedir(dir);
	}
	return (NULL);
}

static	char	*check_current_dir(char *exec)
{
	char	*pwd;
	char	*tmp;
	char	*full_path;

	if (exec[0])
	{
		pwd = getcwd(NULL, 0);
		tmp = ft_strjoin(pwd, "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, exec);
		free (tmp);
		if (!full_path)
			return (NULL);
		if (!access(full_path, R_OK | X_OK))
		{
			free(pwd);
			return (full_path);
		}
		free(pwd);
		free(full_path);
	}
	g_sig = 127;
	return (ft_printf(2, E_SHELL_PERROR, exec, "command not found"), NULL);
}

static char	*valid_exec(char *exec, char **path_env)
{
	char	*full_path;
	char	*tmp;
	int		i;

	if (!ft_strncmp(exec, "./", 2)
		|| (!ft_strncmp(exec, "/", 1)))
		return (direct_path(exec));
	i = 0;
	while (exec[0] && path_env && path_env[i])
	{
		tmp = ft_strjoin(path_env[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, exec);
		free (tmp);
		if (!full_path)
			return (NULL);
		if (!access(full_path, R_OK | X_OK))
			return (full_path);
		free(full_path);
		i++;
	}
	return (check_current_dir(exec));
}

static t_bool	period_check(char *args)
{
	if ((ft_strlen(args) == 1 && !ft_strncmp(args, ".", 1))
		|| (ft_strlen(args) == 2 && !ft_strncmp(args, "..", 2)))
	{
		g_sig = 127;
		ft_printf(2, E_SHELL_PERROR, args, "command not found");
		return (t);
	}
	return (f);
}

int	get_exec_path(t_cmd *cmd, t_list *env_list)
{
	char	*exec_path;
	char	**path_list;
	t_env	*path_env;

	if (cmd->args[0])
	{
		path_env = get_env(env_list, "PATH");
		path_list = NULL;
		if (path_env)
			path_list = ft_split(path_env->value, ':');
		exec_path = valid_exec(cmd->args[0], path_list);
		if (path_list)
			ft_freematrix((void **)path_list);
		if (!period_check(cmd->args[0]) && exec_path)
		{
			free(cmd->args[0]);
			cmd->args[0] = exec_path;
			return (0);
		}
	}
	return (-1);
}
