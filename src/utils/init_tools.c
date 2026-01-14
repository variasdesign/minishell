/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:27:26 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 18:41:15 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If PWD is not found in env, initialize it using getcwd().
// If PATH is not found in env, initialize it with a default sane value.
static	void	default_envs(t_list *env)
{
	char	*pwd;

	if (!get_env(env, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		add_env(env, "PWD", pwd);
	}
	if (!get_env(env, "PATH"))
		add_env(env, "PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin");
}

// Simple loop to allocate tables and deallocate them if there were allocations
// previous to the failed one.
static t_mini	*allocate_tables(t_mini *msh, t_ptr_tab **tables)
{
	size_t		i;

	i = 0;
	while (i < TABLE_NUM)
	{
		tables[i] = ft_calloc(1, sizeof(t_ptr_tab));
		if (!tables[i])
		{
			ft_printf(2, "Error allocating minishell pointer tables: %s\n",
				strerror(errno));
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

// Initialize environment by making a hard copy of envp into a linked list.
static t_list	*init_env(char **envp)
{
	t_list	*env_list;
	t_node	*env_node;
	t_env	content;
	size_t	i;

	env_list = ft_lstnew_list(sizeof(t_env));
	i = 0;
	while (envp && envp[i])
	{
		content.key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		content.value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		env_node = ft_lstnew_node(sizeof(t_env), &content);
		ft_lstadd_back(env_list, env_node);
		i++;
	}
	default_envs(env_list);
	return (env_list);
}

// Initialize main minishell structure. First, we declare a fixed-length
// 2D array containing all tables. This is just a convenience to initialize
// them with a loop. Then we allocate all tables and make a hard copy of env
// into a linked list. The rest are default values.
t_mini	*allocate_minishell(char **envp)
{
	t_mini		*msh;
	t_ptr_tab	*tables[TABLE_NUM];

	msh = ft_calloc(1, sizeof(t_mini));
	if (!msh)
	{
		ft_printf(2, "Error allocating minishell struct: %s", strerror(errno));
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
	msh->prompt = NULL;
	msh->input = NULL;
	msh->loop = t;
	msh->cmd_since_last_pipe = f;
	return (msh);
}
