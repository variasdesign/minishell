/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:09:19 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/08 15:14:01 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_single_builtin(t_cmd *cmd, char ***env)
{
	int	exit_status;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	
	if (dup2(cmd->fd_in, STDIN_FILENO) < 0
		|| dup2(cmd->fd_out, STDOUT_FILENO) < 0)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	
	exit_status = exec_builtin(cmd->args, env);
	
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	
	return (exit_status);
}

int	exec_cmd_list(t_mini *msh, t_list *cmd_list, char **env)
{
	int		i;
	int		status;
	t_node	*cmd;
	t_cmd	*cmd_content;

	if (cmd_list->count == 1)
	{
		cmd = cmd_list->head;
		cmd_content = (t_cmd *)cmd->content;
		if (cmd_content->args && cmd_content->args[0] 
			&& is_builtin(cmd_content->args[0]))
		{
			return (exec_single_builtin(cmd_content, &msh->env));
		}
	}
	
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
