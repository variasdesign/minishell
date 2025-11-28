/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:38:08 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:49:43 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *msg, char *err, int exit_code)
{
	print_error(msg, err);
	exit(exit_code);
}

void	print_error(char *msg, char *err)
{
	if (!err && !msg)
		perror(NULL);
	else if (!msg)
		ft_printf(2, "%s\n", err);
	else if (!err)
		ft_printf(2, msg);
	else
		ft_printf(2, msg, err);
}

int	check_fd_errors(t_cmd *cmd)
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
