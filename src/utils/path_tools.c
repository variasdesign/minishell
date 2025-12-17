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

static char	*valid_exec(char *exec, char **path_env)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(exec, '/'))
		if (access(exec, R_OK | X_OK) == 0)
			return (ft_strdup(exec));
	while (path_env[i])
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
	return (NULL);
}

int	get_exec_path(t_cmd *cmd, t_list *env_list)
{
	char	*exec_path;
	char	*path_env;
	char	**path_list;

	path_env = get_env(env_list, "PATH")->value;
	if (!path_env)
		return (-1);
	path_list = ft_split(path_env, ':');
	exec_path = valid_exec(cmd->args[0], path_list);
	ft_freematrix((void **)path_list);
	if (!exec_path)
	{
		g_sig = 127;
		ft_printf(2, E_SHELL_PERROR, cmd->args[0], "command not found");
		return (-1);
	}
	free(cmd->args[0]);
	cmd->args[0] = exec_path;
	return (0);
}
