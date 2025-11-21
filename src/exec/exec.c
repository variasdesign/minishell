/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:09:19 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/21 14:43:31 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_multiple(t_list *cmd_list)
{
	(void) cmd_list;
	return (0);
}

static int	exec_single(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork_and_exec_single(cmd, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && pid != -1)
		return (WEXITSTATUS(status));
	else
		return (-1);
}

int	exec_input(t_list *cmd_list, char **env)
{
	if (cmd_list->count > 1)
		return (exec_multiple(cmd_list));
	else if (cmd_list->count == 1)
		return (exec_single(cmd_list->head->content, env));
	else
		return (-1);
}
