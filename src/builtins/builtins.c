/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2025/12/15 19:23:52 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_standalone_builtin(t_builtin builtin)
{
	if (builtin == CMD_CD
		|| builtin == CMD_EXIT
		|| builtin == CMD_EXPORT
		|| builtin == CMD_UNSET)
		return (t);
	return (f);
}

t_builtin	is_builtin(t_cmd *cmd)
{
	char	*arg;

	if (cmd->args && cmd->args[0])
	{
		arg = cmd->args[0];
		if (ft_strncmp(arg, "cd", 2) == 0 && ft_strlen(arg) == 2)
			return (CMD_CD);
		if (ft_strncmp(arg, "echo", 4) == 0 && ft_strlen(arg) == 4)
			return (CMD_ECHO);
		if (ft_strncmp(arg, "env", 3) == 0 && ft_strlen(arg) == 3)
			return (CMD_ENV);
		if (ft_strncmp(arg, "exit", 4) == 0 && ft_strlen(arg) == 4)
			return (CMD_EXIT);
		if (ft_strncmp(arg, "export", 6) == 0 && ft_strlen(arg) == 6)
			return (CMD_EXPORT);
		if (ft_strncmp(arg, "pwd", 3) == 0 && ft_strlen(arg) == 3)
			return (CMD_PWD);
		if (ft_strncmp(arg, "unset", 5) == 0 && ft_strlen(arg) == 5)
			return (CMD_UNSET);
	}
	return (CMD_NULL);
}

int	exec_single_builtin(t_mini *msh, t_cmd *cmd, t_list *env_list)
{
	const t_builtin	builtin = is_builtin(cmd);

	if (!cmd->args || !cmd->args[0])
		return (1);
	if (builtin == CMD_CD)
		g_sig = builtin_cd(cmd->args, env_list);
	if (builtin == CMD_EXIT)
		msh->loop = f;
	if (builtin == CMD_EXPORT)
		g_sig = builtin_export(cmd->args, env_list);
	if (builtin == CMD_UNSET)
		g_sig = builtin_unset(cmd->args, env_list);
	return (g_sig);
}

int	exec_builtin(t_cmd *cmd, t_list *env_list)
{
	const t_builtin	builtin = is_builtin(cmd);

	if (!cmd->args || !cmd->args[0])
		return (-1);
	if (builtin == CMD_CD)
		g_sig = builtin_cd(cmd->args, env_list);
	if (builtin == CMD_ECHO)
		g_sig = builtin_echo(cmd->args);
	if (builtin == CMD_ENV)
		g_sig = builtin_env(cmd->args, env_list);
	if (builtin == CMD_EXIT)
		g_sig = builtin_exit(cmd->args);
	if (builtin == CMD_EXPORT)
		g_sig = builtin_export(cmd->args, env_list);
	if (builtin == CMD_PWD)
		g_sig = builtin_pwd();
	if (builtin == CMD_UNSET)
		g_sig = builtin_unset(cmd->args, env_list);
	return (0);
}
