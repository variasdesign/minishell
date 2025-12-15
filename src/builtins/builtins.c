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

int	is_builtin(t_cmd *cmd)
{
	char	*arg;

	arg = cmd->args[0];
	if (ft_strncmp(arg, "cd", 2) == 0 && ft_strlen(arg) == 2)
		return (1);
	if (ft_strncmp(arg, "pwd", 3) == 0 && ft_strlen(arg) == 3)
		return (1);
	if (ft_strncmp(arg, "echo", 4) == 0 && ft_strlen(arg) == 4)
		return (1);
	if (ft_strncmp(arg, "env", 3) == 0 && ft_strlen(arg) == 3)
		return (1);
	if (ft_strncmp(arg, "export", 6) == 0 && ft_strlen(arg) == 6)
		return (1);
	if (ft_strncmp(arg, "unset", 5) == 0 && ft_strlen(arg) == 5)
		return (1);
	if (ft_strncmp(arg, "exit", 4) == 0 && ft_strlen(arg) == 4)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_list *env_list)
{
	char	*arg;

	if (!cmd->args || !cmd->args[0])
		return (1);
	arg = cmd->args[0];
	if (ft_strncmp(arg, "cd", 2) == 0 && ft_strlen(arg) == 2)
		g_sig = builtin_cd(cmd->args, env_list);
	if (ft_strncmp(arg, "pwd", 3) == 0 && ft_strlen(arg) == 3)
		g_sig = builtin_pwd();
	if (ft_strncmp(arg, "echo", 4) == 0 && ft_strlen(arg) == 4)
		g_sig = builtin_echo(cmd->args, NULL);
	if (ft_strncmp(arg, "env", 3) == 0 && ft_strlen(arg) == 3)
		g_sig = builtin_env(cmd->args, env_list);
	if (ft_strncmp(arg, "export", 6) == 0 && ft_strlen(arg) == 6)
		g_sig = builtin_export(cmd->args, env_list);
	if (ft_strncmp(arg, "unset", 5) == 0 && ft_strlen(arg) == 5)
		g_sig = builtin_unset(cmd->args, env_list);
	if (ft_strncmp(arg, "exit", 4) == 0 && ft_strlen(arg) == 4)
		g_sig = builtin_exit(cmd->args);
	return (0);
}
