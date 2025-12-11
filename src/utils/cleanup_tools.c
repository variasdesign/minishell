/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:03:24 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/10 19:00:56 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(void *env_ptr)
{
	t_env	*env;

	env = env_ptr;
	free(env->key);
	free(env->value);
	free(env);
}

void	free_cmd_list(void *cmd_ptr)
{
	t_cmd	*cmd;

	cmd = cmd_ptr;
	ft_freematrix((void **)cmd->args);
	ft_lstdel_list(cmd->redir_list, free);
	free(cmd);
}

void	free_tables(t_mini *msh, t_bool free_full_table)
{
	t_ptr_tab	*tables[TABLE_NUM];
	int			i;

	tables[0] = msh->squote_tab;
	tables[1] = msh->dquote_tab;
	tables[2] = msh->var_tab;
	tables[3] = msh->redir_tab;
	tables[4] = msh->word_tab;
	i = -1;
	while (++i < TABLE_NUM)
		tables[i] = ft_tabfree(&tables[i], free_full_table);
}

void	free_all(t_mini *msh)
{
	msh->env = ft_lstdel_list(msh->env, free_env_list);
	if (msh->cwd)
		free(msh->cwd);
	if (msh->input)
		free(msh->input);
	if (msh->prompt)
		free(msh->prompt);
	free_tables(msh, t);
	free(msh);
}

void	child_cleanup_and_exit(t_mini *msh, int exit_code)
{
	ft_lstdel_list(msh->cmd_list, free_cmd_list);
	free(msh->pids);
	free_all(msh);
	exit(exit_code);
}
