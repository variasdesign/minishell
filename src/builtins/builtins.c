/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2026/01/05 15:27:00 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if the command word matches with a builtin.
t_builtin	is_builtin(t_cmd *cmd)
{
	char	*arg;

	if (cmd->args[0] && cmd->args[0][0])
	{
		arg = cmd->args[0];
		if (ft_strncmp(arg, "cd", 2) == 0 && ft_strlen(arg) == 2)
			return (CMD_CD);
		else if (ft_strncmp(arg, "echo", 4) == 0 && ft_strlen(arg) == 4)
			return (CMD_ECHO);
		else if (ft_strncmp(arg, "env", 3) == 0 && ft_strlen(arg) == 3)
			return (CMD_ENV);
		else if (ft_strncmp(arg, "exit", 4) == 0 && ft_strlen(arg) == 4)
			return (CMD_EXIT);
		else if (ft_strncmp(arg, "export", 6) == 0 && ft_strlen(arg) == 6)
			return (CMD_EXPORT);
		else if (ft_strncmp(arg, "pwd", 3) == 0 && ft_strlen(arg) == 3)
			return (CMD_PWD);
		else if (ft_strncmp(arg, "unset", 5) == 0 && ft_strlen(arg) == 5)
			return (CMD_UNSET);
	}
	return (CMD_NULL);
}

// Call the builtin function associated with its builtin command.
t_cmd	*exec_builtin(t_cmd *cmd, t_list *env_list, t_bool *loop)
{
	const t_builtin	builtin = is_builtin(cmd);

	if (!cmd->args[0] || !cmd->args[0][0])
		g_sig = -1;
	else if (builtin == CMD_CD)
		g_sig = builtin_cd(cmd->args, env_list);
	else if (builtin == CMD_ECHO)
		g_sig = builtin_echo(cmd->args);
	else if (builtin == CMD_ENV)
		g_sig = builtin_env(cmd->args, env_list);
	else if (builtin == CMD_EXIT)
		g_sig = builtin_exit(cmd->args, loop);
	else if (builtin == CMD_EXPORT)
		g_sig = builtin_export(cmd->args, env_list);
	else if (builtin == CMD_PWD)
		g_sig = builtin_pwd(get_env(env_list, "PWD"));
	else if (builtin == CMD_UNSET)
		g_sig = builtin_unset(cmd->args, env_list);
	return (cmd);
}

int	exec_single_builtin(t_cmd *cmd, t_list *env_list, t_bool *loop)
{
	int	orig_fd_in;
	int	orig_fd_out;

	if (open_files(cmd, env_list) < 0)
		return (-1);
	orig_fd_in = dup(STDIN_FILENO);
	orig_fd_out = dup(STDOUT_FILENO);
	if (dup2_fds(cmd))
		return (-1);
	exec_builtin(cmd, env_list, loop);
	close_fds(cmd);
	cmd->fd_in = orig_fd_in;
	cmd->fd_out = orig_fd_out;
	if (dup2_fds(cmd))
		return (-1);
	close_fds(cmd);
	return (0);
}
