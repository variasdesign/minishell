/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:28:50 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/21 14:40:17 by varias-c         ###   ########.fr       */
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

static int	exec_wrapper(t_cmd *cmd, char **env)
{
	char	*exec_path;
	char	*path_env;
	char	**path_list;

	path_env = get_env(env, "PATH");
	if (!path_env)
	{
		printf("PATH not found!\n");
		return (-1);
	}
	path_list = ft_split(path_env, ':');
	exec_path = valid_exec(cmd->args[0], path_list);
	if (!exec_path)
	{
		printf("Executable not found: %s.\n", cmd->args[0]);
		ft_freematrix((void **)cmd->args);
		return (-1);
	}
	free(cmd->args[0]);
	free(path_list);
	cmd->args[0] = exec_path;
	if (execve(cmd->args[0], cmd->args, env))
		ft_freematrix((void **)cmd->args);
	perror(NULL);
	return (-1);
}

pid_t	fork_and_exec_single(t_cmd *cmd, char **env)
{
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
	{
		perror("Error creating fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (exec_wrapper(cmd, env) < 0)
		{
			perror("Error executing command");
			close(STDOUT_FILENO);
			return (-1);
		}
	}
	return (pid);
}
