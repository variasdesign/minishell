/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:27:26 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/07 19:43:49 by varias-c         ###   ########.fr       */
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

t_mini	*allocate_minishell(void)
{
	t_mini		*msh;
	t_ptr_tab	*tables[5];

	msh = ft_calloc(1, sizeof(t_mini));
	if (!msh)
	{
		perror("Error allocating minishell struct");
		return (NULL);
	}
	msh = allocate_tables(msh, tables);
	if (!msh)
		return (NULL);
	msh->squote_tab = tables[0];
	msh->dquote_tab = tables[1];
	msh->var_tab = tables[2];
	msh->word_tab = tables[3];
	msh->redir_tab = tables[4];
	return (msh);
}
