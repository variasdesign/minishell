/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:27:26 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:42:29 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini	*allocate_tables(t_mini *msh, t_ptr_tab **tables)
{
	size_t		i;

	i = 0;
	while (i < TABLE_NUM)
	{
		tables[i] = ft_calloc(1, sizeof(t_ptr_tab));
		if (!tables[i])
		{
			perror("Error allocating minishell pointer tables");
			while (i-- > 0)
			{
				free(tables[i]);
				tables[i] = NULL;
			}
			free(msh);
			msh = NULL;
			return (NULL);
		}
		i++;
	}
	return (msh);
}

static char	**init_env(char **envp)
{
	char	**env_copy;
	size_t	env_count;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	env_copy = ft_calloc(env_count + 1, sizeof(char *));
	env_count = 0;
	while (envp[env_count])
	{
		env_copy[env_count] = ft_strdup(envp[env_count]);
		env_count++;
	}
	return (env_copy);
}

t_mini	*allocate_minishell(char **envp)
{
	t_mini		*msh;
	t_ptr_tab	*tables[TABLE_NUM];

	msh = ft_calloc(1, sizeof(t_mini));
	if (!msh)
	{
		perror("Error allocating minishell struct");
		return (NULL);
	}
	msh = allocate_tables(msh, tables);
	if (!msh)
		return (NULL);
	msh->env = init_env(envp);
	msh->squote_tab = tables[0];
	msh->dquote_tab = tables[1];
	msh->var_tab = tables[2];
	msh->redir_tab = tables[3];
	msh->word_tab = tables[4];
	msh->exit_code = 0;
	msh->cwd = getcwd(NULL, 0);
	msh->path = get_env(msh->env, "PATH");
	msh->loop = t;
	return (msh);
}
