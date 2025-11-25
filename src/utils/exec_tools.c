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

static int	child_process(t_cmd *cmd, char **env, int fd[2])
{
	close(fd[0]);
	if (dup2(px->in, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
	{
		close(fd[1]);
		close(px->in);
		return (-1);
	}
	close(fd[1]);
	close(px->in);
	if (exec_wrapper(px, arg) < 0)
	{
		close(STDOUT_FILENO);
		print_error(E_EXEC_FAILURE, strerror(errno));
		return (-1);
	}
	return (0);
}

pid_t	fork_and_exec(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
	{
		print_error(E_PIPE_FAILURE, strerror(errno));
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		print_error(E_FORK_FAILURE, strerror(errno));
		return (-1);
	}
	if (pid == 0)
		if (child_process(cmd, env, fd) < 0)
			disassemble_child(cmd, t, f);
	close(fd[1]);
	close(cmd->fd_in);
	return (pid);
}

pid_t	fork_and_exec_last(t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print_error(E_FORK_FAILURE, strerror(errno));
		return (-1);
	}
	if (pid == 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0 || dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			disassemble_child(px, f, t);
		close(cmd->fd_in);
		close(cmd->fd_out);
		if (open_files(cmd) < 0 || exec_wrapper(cmd, env) < 0)
		{
			close(STDOUT_FILENO);
			print_error(E_EXEC_FAILURE, strerror(errno));
			disassemble_child(px, f, t);
			exit(127);
		}
	}
	close(cmd->fd_in);
	close(cmd->fd_out);
	return (pid);
}
