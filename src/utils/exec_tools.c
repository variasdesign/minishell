/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:28:50 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/08 19:13:34 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cleanup the temporary heredoc file. We wanted to use O_TMPFILE
// in the heredoc call to avoid creating a file but it doesn't work correctly.
static void	cleanup_heredoc(t_list *redir_list)
{
	t_node	*redir_node;
	t_redir	*redir;

	if (redir_list)
	{
		redir_node = redir_list->head;
		while (redir_node)
		{
			redir = redir_node->content;
			if (redir->type == TOKEN_REDIR_HEREDOC)
				unlink("/tmp/heredoc");
			redir_node = redir_node->next;
		}
	}
}

// Duplicate the opened file descriptors into STDIN and STDOUT.
int	dup2_fds(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) < 0
		|| dup2(cmd->fd_out, STDOUT_FILENO) < 0)
	{
		ft_perror(E_DUP_FAILURE, strerror(errno), f, 0);
		return (-1);
	}
	return (0);
}

// Close the original opened file descriptors, either from pipe()
// or from open_files(), since they are already duped into STDIN and STDOUT.
void	close_fds(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}

// If the command word is not empty, execute it. First, reassemble the linked
// list environment into a 2D array for execve to use. Then, set the writing
// end of the pipe (if present) as output. Then, duplicate file descriptors
// into STDIN and STDOUT and close the originals. Finally, check if the command
// is a builtin or not, executing with execve if not, else calling exec_builtin.
static t_cmd	*child_process(t_cmd *cmd, t_list *env_list, int fd[2])
{
	exec_signal();
	if (cmd->args[0])
	{
		cmd->env = reassemble_env(env_list);
		if (cmd->pipe_to && cmd->fd_out == STDOUT_FILENO)
		{
			cmd->fd_out = fd[1];
			close(fd[0]);
		}
		if (dup2_fds(cmd))
		{
			g_sig = -1;
			return (ft_perror(E_DUP_FAILURE, strerror(errno), f, 0), cmd);
		}
		close_fds(cmd);
		if (!is_builtin(cmd) && execve(cmd->args[0], cmd->args,
				cmd->env))
		{
			g_sig = -1;
			return (cmd);
		}
		return (exec_builtin(cmd, env_list, NULL));
	}
	return (NULL);
}

// Create a pipe (if needed), open redirections (if any), fork and execute.
// If the execution fails for any reason, child_cleanup is called. The parent
// also performs some cleanup and sets the reading end of the pipe for
// the next command to use as input.
pid_t	fork_and_exec(t_mini *msh, t_node *cmd_node, t_list *env_list)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*cmd[2];

	cmd[0] = cmd_node->content;
	if (cmd[0]->pipe_to && pipe(fd) < 0)
		return (ft_perror(E_PIPE_FAILURE, strerror(errno), f, 0), -1);
	if (open_files(cmd[0], env_list) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (ft_perror(E_FORK_FAILURE, strerror(errno), f, 0), -1);
	if (pid == 0)
		child_cleanup(msh, child_process(cmd[0], env_list, fd));
	close_fds(cmd[0]);
	if (cmd[0]->pipe_to)
	{
		close(fd[1]);
		cmd[1] = cmd_node->next->content;
		cmd[1]->fd_in = fd[0];
	}
	cleanup_heredoc(cmd[0]->redir_list);
	return (pid);
}
