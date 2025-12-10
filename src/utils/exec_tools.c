/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:28:50 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/10 19:29:52 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(t_cmd *cmd, char **env, int fd[2])
{
	if (open_files(cmd, env) < 0)
		return (-1);
	if (cmd->pipe_to)
		cmd->fd_out = fd[1];
	if (dup2(cmd->fd_in, STDIN_FILENO) < 0
		|| dup2(cmd->fd_out, STDOUT_FILENO) < 0)
	{
		ft_perror(E_DUP_FAILURE, strerror(errno), f, 0);
		return (-1);
	}
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (!is_builtin(cmd) && execve(cmd->args[0], cmd->args, env))
		return (-1);
	return (exec_builtin(cmd, &env));
}

pid_t	fork_and_exec(t_mini *msh, t_node *cmd_node, char **env)
{
	int		child_exit_code;
	int		fd[2];
	pid_t	pid;
	t_cmd	*cmd;

	cmd = cmd_node->content;
	if (cmd->pipe_to && pipe(fd) < 0)
		return (ft_perror(E_PIPE_FAILURE, strerror(errno), f, 0), -1);
	pid = fork();
	if (pid < 0)
		return (ft_perror(E_FORK_FAILURE, strerror(errno), f, 0), -1);
	if (pid == 0)
	{
		child_exit_code = child_process(cmd_node->content, env, fd);
		if (child_exit_code < 0)
			child_cleanup_and_exit(msh, EXIT_FAILURE);
		child_cleanup_and_exit(msh, child_exit_code);
	}
	if (cmd->pipe_to)
	{
		close(fd[1]);
		cmd = cmd_node->next->content;
		cmd->fd_in = fd[0];
	}
	return (pid);
}
