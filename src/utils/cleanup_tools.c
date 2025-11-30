/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:03:24 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:47:27 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(void *cmd_ptr)
{
	t_cmd *cmd;

	cmd = cmd_ptr;
	ft_freematrix((void **)cmd->args);
	ft_lstdel_list(cmd->redir_list, free);
	free(cmd);
}

void	free_all(t_mini *msh)
{
	t_ptr_tab	*tables[TABLE_NUM];
	int			i;

	msh->env = (char **)ft_freematrix((void **)msh->env);
	free(msh->cwd);
	tables[0] = msh->squote_tab;
	tables[1] = msh->dquote_tab;
	tables[2] = msh->var_tab;
	tables[3] = msh->redir_tab;
	tables[4] = msh->word_tab;
	i = -1;
	while (++i < TABLE_NUM)
		tables[i] = ft_tabfree(&tables[i], t);
	free(msh);
}
