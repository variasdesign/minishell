/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:31:31 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/15 21:02:01 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_fd_errors(t_cmd *cmd)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
	{
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		return (-1);
	}
	return (0);
}

static int	open_input(char *path)
{
	if (!access(path, F_OK | R_OK))
		return (open(path, O_RDONLY));
	else
	{
		ft_printf(2, E_SHELL_PERROR, path, strerror(errno));
		return (-1);
	}
	return (0);
}

static int	open_output(char *path, t_bool append)
{
	int	out;

	if (access(path, W_OK))
	{
		if (errno != ENOENT)
			return (ft_printf(2, E_SHELL_PERROR, path, strerror(errno)), -1);
		else
			out = open(path, O_WRONLY | O_CREAT, 0640);
	}
	else
	{
		if (append)
			out = open(path, O_WRONLY | O_APPEND);
		else
			out = open(path, O_WRONLY | O_TRUNC);
	}
	if (out < 0)
		return (ft_printf(2, E_SHELL_PERROR, path, strerror(errno)), -1);
	return (out);
}

// FIX: If one redirection fails, skip the rest
static void	open_redirections(t_cmd *cmd)
{
	t_node			*node;
	t_token_type	type;
	char			*path;

	node = cmd->redir_list->head;
	while (node)
	{
		type = get_token_type(node);
		path = ((t_redir *)(node->content))->file;
		if (!cmd->pipe_from && (type == TOKEN_REDIR_IN
				|| (type == TOKEN_REDIR_HEREDOC && heredoc(path))))
		{
			if (cmd->fd_in != STDIN_FILENO)
				close(cmd->fd_in);
			cmd->fd_in = open_input(path);
		}
		else if (!cmd->pipe_to
			&& (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_APPEND))
		{
			if (cmd->fd_out != STDOUT_FILENO)
				close(cmd->fd_out);
			cmd->fd_out = open_output(path, type == TOKEN_REDIR_APPEND);
		}
		node = node->next;
	}
}

int	open_files(t_cmd *cmd, t_list *env_list)
{
	if (!is_builtin(cmd) && get_exec_path(cmd, env_list) < 0)
		return (-1);
	if (cmd->redir_list)
		open_redirections(cmd);
	return (check_fd_errors(cmd));
}
