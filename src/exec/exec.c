/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:09:19 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/10 19:31:00 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pids_and_exec(t_mini *msh, t_list *cmd_list,
								t_list *env_list, int *status)
{
	ssize_t	i;
	t_node	*cmd;

	i = 0;
	msh->pids = ft_calloc(cmd_list->count + 1, sizeof(pid_t));
	cmd = cmd_list->head;
	while (i < cmd_list->count && cmd)
	{
		msh->pids[i] = fork_and_exec(msh, cmd, env_list);
		i++;
		cmd = cmd->next;
	}
	i = -1;
	while (++i < cmd_list->count)
	{
		if (msh->pids[i] != -1)
		{
			waitpid(msh->pids[i], status, 0);
			if (WIFEXITED(*status))
				g_sig = WEXITSTATUS(*status);
		}
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
		if (cmd_list->count == 1 && is_standalone_builtin(is_builtin(cmd)))
			g_sig = exec_single_builtin(cmd, env_list, &msh->loop);
		else
			init_pids_and_exec(msh, cmd_list, env_list, &status);
	}
	return (g_sig);
}
