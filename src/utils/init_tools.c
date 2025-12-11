/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:27:26 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/01 13:24:32 by varias-c         ###   ########.fr       */
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

static t_list *init_env(char **envp)
{
	t_list	*env_list;
	t_node	*env_node;
	t_env	content;
	size_t	i;

	env_list = ft_lstnew_list(sizeof(t_env));
	i = 0;
	while (envp[i])
	{
		content.key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		content.value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		env_node = ft_lstnew_node(sizeof(t_env), &content);
		ft_lstadd_back(env_list, env_node);
		i++;
	}
	return (env_list);
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
	msh->cwd = getcwd(NULL, 0);
	msh->prompt = NULL;
	msh->input = NULL;
	msh->loop = t;
	return (msh);
}
