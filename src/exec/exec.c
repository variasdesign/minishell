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

static int	exec_multiple(t_list *cmd_list, char **env)
{
	pid_t	*pids;
	int		i;
	int		status;
	t_node	*cmd;

	i = 0;
	pids = ft_calloc(cmd_list->count + 1, sizeof(pid_t));
	cmd = cmd_list->head;
	while (i < cmd_list->count && cmd)
	// while (i < cmd_list->count - 1)
	{
		pids[i] = fork_and_exec(cmd, env, !cmd->next);
		i++;
		cmd = cmd->next;
	}
	// pids[i] = fork_and_exec_last(ft_lstfind_node(cmd_list, i)->content, env);
	i = 0;
	while (i < cmd_list->count)
		waitpid(pids[i++], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

static int	exec_single(t_node *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork_and_exec(cmd, env, !cmd->next);
	// pid = fork_and_exec_last(cmd, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && pid != -1)
		return (WEXITSTATUS(status));
	else
		return (-1);
}

int	exec_input(t_list *cmd_list, char **env)
{
	if (cmd_list->count > 1)
		return (exec_multiple(cmd_list, env));
	else if (cmd_list->count == 1)
		return (exec_single(cmd_list->head, env));
	else
		return (-1);
}
