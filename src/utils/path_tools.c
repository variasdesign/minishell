/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:25:35 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/01 13:15:26 by varias-c         ###   ########.fr       */
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

static char	*valid_exec(char *exec, char **path_env)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strncmp(exec, "./", 2)
		|| (!ft_strncmp(exec, "/", 1)))
		return (direct_path(exec));
	while (exec[0] && path_env[i])
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
	g_sig = 127;
	ft_printf(2, E_SHELL_PERROR, exec, "command not found");
	return (NULL);
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
		if (!path_env)
			return (ft_printf(2, E_SHELL_PERROR,
					cmd->args[0], "No such file or directory"), -1);
		path_list = ft_split(path_env->value, ':');
		exec_path = valid_exec(cmd->args[0], path_list);
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
