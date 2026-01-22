/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:45:01 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/22 19:18:47 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_error(char *exec, DIR *dir)
{
	const char	*error = strerror(errno);

	if (!ft_strncmp(error, "No such file or directory", ft_strlen(error)))
	{
		g_sig = 127;
		return (ft_printf(2, E_SHELL_PERROR, exec, "command not found"), NULL);
	}
	else if (!ft_strncmp(error, "Permission denied", ft_strlen(error)))
	{
		g_sig = 126;
		return (ft_printf(2, E_SHELL_PERROR, exec, "Permission denied"), NULL);
	}
	else if (dir)
	{
		g_sig = 126;
		return (ft_printf(2, E_SHELL_PERROR, exec, "Is a directory"), NULL);
	}
	g_sig = 1;
	return (ft_printf(2, E_SHELL_PERROR, exec, "unknown error"), NULL);
}

char	*assemble_path(char *exec, char *path_env)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(path_env, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, exec);
	free (tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}
