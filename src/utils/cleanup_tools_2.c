/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:23:18 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/16 14:24:02 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_cleanup(t_mini *msh, int exit_code)
{
	ft_lstdel_list(msh->cmd_list, free_cmd_list);
	free(msh->pids);
	free_all(msh);
	if (exit_code != -1)
		exit(exit_code);
	exit(EXIT_FAILURE);
}
