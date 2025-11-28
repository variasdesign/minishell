/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:31:31 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:49:41 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(void)
{
	int	hd_fd;

	hd_fd = open("/tmp/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (hd_fd < 0)
	{
		print_error(E_HEREDOC_FAILURE, NULL);
		return (-1);
	}
	return (hd_fd);
}

static int	heredoc(char *lim)
{
	const int	heredoc_fd = open_heredoc();
	const int	lim_len = ft_strlen(lim);
	char		*line;

	if (heredoc_fd < 0)
		return (-1);
	while (t)
	{
		line = get_next_line(0);
		if (!line)
		{
			print_error(E_HEREDOC_FAILURE, NULL);
			return (-1);
		}
		if (!ft_strncmp(line, lim, lim_len) && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
		free(line);
	}
	close(heredoc_fd);
	return (0);
}

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
			return (ft_printf(2, E_UNWRITABLE_OUTPUT, strerror(errno)), 1);
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

int	open_files(t_cmd *cmd, int fd[2])
{
	t_node			*node;
	t_token_type	type;
	char			*path;

	if (cmd->redir_list)
	{
		node = cmd->redir_list->head;
		while (node)
		{
			type = get_token_type(node);
			path = ((t_redir *)(node->content))->file;
			if (type == TOKEN_REDIR_IN
				|| (type == TOKEN_REDIR_HEREDOC && heredoc(path)))
			{
				if (cmd->fd_in != STDIN_FILENO)
					close(cmd->fd_in);
				cmd->fd_in = open_input(path);
			}
			else if (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_APPEND)
			{
				if (cmd->fd_out != STDOUT_FILENO)
					close(cmd->fd_out);
				cmd->fd_out = open_output(path, type == TOKEN_REDIR_APPEND);
			}
			node = node->next;
		}
	}
	if (cmd->pipe_from)
		cmd->fd_in = fd[0];
	if (cmd->pipe_to)
		cmd->fd_out = fd[1];
	return (check_fd_errors(cmd));
}
