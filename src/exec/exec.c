/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:09:19 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/01 13:10:43 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_list(t_mini *msh, t_list *cmd_list, char **env)
{
	int		i;
	int		status;
	t_node	*cmd;

	if (cmd_list->count > 0)
	{
		i = 0;
		msh->pids = ft_calloc(cmd_list->count + 1, sizeof(pid_t));
		cmd = cmd_list->head;
		while (i < cmd_list->count && cmd)
		{
			msh->pids[i] = fork_and_exec(msh, cmd, env);
			i++;
			cmd = cmd->next;
		}
		i = 0;
		while (i < cmd_list->count)
			waitpid(msh->pids[i++], &status, 0);
		free(msh->pids);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}
