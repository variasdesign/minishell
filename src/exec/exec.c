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
	int		i;
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
	i = 0;
	while (i < cmd_list->count)
	{
		waitpid(msh->pids[i++], status, 0);
		if (WIFEXITED(*status))
			g_sig = WEXITSTATUS(*status);
	}
	free(msh->pids);
}

int	exec_cmd_list(t_mini *msh, t_list *cmd_list, t_list *env_list)
{
	int	status;

	if (cmd_list->count > 0)
	{
		if (cmd_list->count == 1)
		{
			if (check_exit(cmd_list->head->content))
			{
				msh->loop = f;
				return (0);
			}
			else if (is_builtin(cmd_list->head->content))
				return (exec_builtin(cmd_list->head->content, env_list));
		}
		init_pids_and_exec(msh, cmd_list, env_list, &status);
	}
	return (0);
}
