/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:28:50 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/08 15:11:57 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(t_cmd *cmd, char **env, int fd[2])
{
	// Verificar si es un built-in ANTES de open_files (que modifica el path)
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
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
		exit(exec_builtin(cmd->args, &env));
	}
	
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
	
	if (execve(cmd->args[0], cmd->args, env))
		return (-1);
	return (0);
}

pid_t	fork_and_exec(t_mini *msh, t_node *cmd_node, char **env)
{
	pid_t	pid;
	int		fd[2];
	t_cmd	*curr;
	t_cmd	*next;

	curr = cmd_node->content;
	if (curr->pipe_to && pipe(fd) < 0)
		return (ft_perror(E_PIPE_FAILURE, strerror(errno), f, 0), -1);
	pid = fork();
	if (pid < 0)
		return (ft_perror(E_FORK_FAILURE, strerror(errno), f, 0), -1);
	if (pid == 0)
		if (child_process(cmd_node->content, env, fd) < 0)
			child_cleanup_and_exit(msh, 127);
	if (curr->pipe_to)
	{
		close(fd[1]);
		next = cmd_node->next->content;
		next->fd_in = fd[0];
	}
	return (pid);
}
