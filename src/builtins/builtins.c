/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2025/12/13 16:16:54 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_name(char *cmd)
{
	char	*last_slash;

	if (!cmd)
		return (NULL);
	last_slash = ft_strrchr(cmd, '/');
	if (last_slash)
		return (last_slash + 1);
	return (cmd);
}

int	is_builtin(t_cmd *cmd)
{
	char	*cmd_name;

	cmd_name = get_cmd_name(cmd->args[0]);
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "cd", 2) == 0 && ft_strlen(cmd_name) == 2)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 3) == 0 && ft_strlen(cmd_name) == 3)
		return (1);
	if (ft_strncmp(cmd_name, "echo", 4) == 0 && ft_strlen(cmd_name) == 4)
		return (1);
	if (ft_strncmp(cmd_name, "exit", 4) == 0 && ft_strlen(cmd_name) == 4)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_list *env_list)
{
	char	*cmd_name;

	if (!cmd->args || !cmd->args[0])
		return (1);
	cmd_name = get_cmd_name(cmd->args[0]);
	if (!cmd_name)
		return (1);
	if (ft_strncmp(cmd_name, "cd", 2) == 0 && ft_strlen(cmd_name) == 2)
		g_sig = builtin_cd(cmd->args, env_list);
	if (ft_strncmp(cmd_name, "pwd", 3) == 0 && ft_strlen(cmd_name) == 3)
		g_sig = builtin_pwd();
	if (ft_strncmp(cmd_name, "echo", 4) == 0 && ft_strlen(cmd_name) == 4)
		g_sig = builtin_echo(cmd->args, NULL);
	if (ft_strncmp(cmd_name, "exit", 4) == 0 && ft_strlen(cmd_name) == 4)
		g_sig = builtin_exit(cmd->args);
	return (0);
}
