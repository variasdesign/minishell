/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:31:31 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/08 19:18:32 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_fd_errors(t_cmd *cmd)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
	{
		if (cmd->fd_in > STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out > STDOUT_FILENO)
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
		g_sig = EXIT_FAILURE;
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
	{
		g_sig = EXIT_FAILURE;
		return (ft_printf(2, E_SHELL_PERROR, path, strerror(errno)), -1);
	}
	return (out);
}

static t_node	*open_redirection(t_cmd *cmd, t_node *redir_node,
							t_list *env_list, t_bool expand_vars)
{
	t_token_type	type;
	t_redir			*redir;

	redir = redir_node->content;
	type = redir->type;
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_HEREDOC)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (type == TOKEN_REDIR_HEREDOC && !heredoc(redir->file, env_list, expand_vars))
			cmd->fd_in = open_input("/tmp/heredoc");
		else
			cmd->fd_in = open_input(redir->file);
	}
	else if ((type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_APPEND))
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd->fd_out = open_output(redir->file,
				type == TOKEN_REDIR_APPEND);
	}
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (NULL);
	return (redir_node->next);
}

/// FIX: Skip executable check if a relative path is passed.
int	open_files(t_cmd *cmd, t_list *env_list, t_bool expand_vars)
{
	t_node			*node;

	if (cmd->redir_list)
	{
		node = cmd->redir_list->head;
		while (node)
			node = open_redirection(cmd, node, env_list, expand_vars);
	}
	if (check_fd_errors(cmd) < 0)
		return (-1);
	if (!is_builtin(cmd) && cmd->args[0] && get_exec_path(cmd, env_list) < 0)
		return (-1);
	return (check_fd_errors(cmd));
}
