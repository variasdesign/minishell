/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:31:31 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/24 19:59:29 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input(char *path)
{
	if (!access(path, F_OK | R_OK))
		return (open(path, O_RDONLY));
	else
		print_error(E_UNREADABLE_INPUT, strerror(errno));
	return (0);
}

static int	open_output(char *path, t_bool append)
{
	int	out;

	if (access(path, W_OK))
	{
		if (errno != ENOENT)
		{
			return (ft_printf(2, E_UNWRITABLE_OUTPUT, strerror(errno)), 1);
		}
		else
		{
			out = open(path, O_WRONLY | O_CREAT, 0640);
			if (out < 0)
				return (ft_printf(2, E_UNWRITABLE_OUTPUT, strerror(errno)), 1);
			else
				return (out);
		}
	}
	else
	{
		if (append)
			return (open(path, O_WRONLY | O_APPEND));
		else
			return (open(path, O_WRONLY | O_TRUNC));
	}
}

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

int	open_files(t_cmd *cmd)
{
	t_node			*node;
	t_token_type	type;
	char			*path;

	node = cmd->redir_list->head;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	while (node)
	{
		type = get_token_type(node);
		path = ((t_redir *)(node->content))->file;
		if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_HEREDOC)
		{
			close(STDIN_FILENO);
			cmd->fd_in = open_input(path);
		}
		else if (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_APPEND)
		{
			close(STDOUT_FILENO);
			cmd->fd_out = open_output(path, type == TOKEN_REDIR_APPEND);
		}
		node = node->next;
	}
	return (check_fd_errors(cmd));
}
