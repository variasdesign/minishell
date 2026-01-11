/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:09:19 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/08 18:13:29 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_children(t_list *cmd_list, pid_t *pids, int *status)
{
	ssize_t	i;
	int		tmp_exit_code;
	
	i = -1;
	tmp_exit_code = g_sig;
	while (++i < cmd_list->count)
	{
		if (pids[i] != -1)
		{
			waitpid(pids[i], status, 0);
			if (WIFEXITED(*status))
				g_sig = WEXITSTATUS(*status);
		}
		else
			g_sig = tmp_exit_code;
	}
}

static void	init_pids_and_exec(t_mini *msh, t_list *cmd_list,
								t_list *env_list, int *status)
{
	ssize_t	i;
	t_node	*cmd_node;

	i = -1;
	msh->pids = ft_calloc(cmd_list->count + 1, sizeof(pid_t));
	if (!msh->pids)
		return ;
	cmd_node = cmd_list->head;
	while (++i < cmd_list->count && cmd_node)
	{
		msh->pids[i] = fork_and_exec(msh, cmd_node, env_list);
		cmd_node = cmd_node->next;
	}
	wait_for_children(cmd_list, msh->pids, status);
	free(msh->pids);
}

/// TODO: If multiple commands are passed as stdin
/// and one of those commands fail
/// the ones after shouldn't be executed.
int	exec_cmd_list(t_mini *msh, t_list *cmd_list, t_list *env_list)
{
	int		status;
	t_cmd	*cmd;

	if (cmd_list->count > 0)
	{
		cmd = cmd_list->head->content;
		if (cmd_list->count == 1 && is_builtin(cmd))
			exec_single_builtin(cmd, env_list, &msh->loop);
		else
			init_pids_and_exec(msh, cmd_list, env_list, &status);
	}
	return (g_sig);
}
