/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:09:19 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/06 13:41:43 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pids_and_exec(t_mini *msh, t_list *cmd_list,
								t_list *env_list, int *status)
{
	ssize_t	i;
	t_node	*cmd;
	int		tmp_exit_code;

	i = 0;
	msh->pids = ft_calloc(cmd_list->count + 1, sizeof(pid_t));
	if (!msh->pids)
		return ;
	cmd = cmd_list->head;
	while (i < cmd_list->count && cmd)
	{
		msh->pids[i] = fork_and_exec(msh, cmd, env_list);
		i++;
		cmd = cmd->next;
	}
	i = -1;
	tmp_exit_code = g_sig;
	while (++i < cmd_list->count)
	{
		if (msh->pids[i] != -1)
		{
			waitpid(msh->pids[i], status, 0);
			if (WIFEXITED(*status))
				g_sig = WEXITSTATUS(*status);
		}
		else
			g_sig = tmp_exit_code;
	}
	free(msh->pids);
}

int	exec_cmd_list(t_mini *msh, t_list *cmd_list, t_list *env_list)
{
	int		status;
	t_cmd	*cmd;

	if (cmd_list->count > 0)
	{
		cmd = cmd_list->head->content;
		if (cmd_list->count == 1 && is_builtin(cmd))
			exec_single_builtin(cmd, env_list, &msh->loop, msh->heredoc_expand);
		else
			init_pids_and_exec(msh, cmd_list, env_list, &status);
	}
	return (g_sig);
}
