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

static int	exec_cmd_list(t_list *cmd_list, char **env)
{
	pid_t	*pids;
	int		i;
	int		status;
	t_node	*cmd;

	i = 0;
	pids = ft_calloc(cmd_list->count + 1, sizeof(pid_t));
	cmd = cmd_list->head;
	while (i < cmd_list->count && cmd)
	{
		pids[i] = fork_and_exec(cmd, env);
		i++;
		cmd = cmd->next;
	}
	i = 0;
	while (i < cmd_list->count)
		waitpid(pids[i++], &status, 0);
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

int	exec_input(t_list *cmd_list, char **env)
{
	if (cmd_list->count > 0)
		return (exec_cmd_list(cmd_list, env));
	else
		return (-1);
}
