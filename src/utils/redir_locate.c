/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_locate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:24:09 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/11 18:42:58 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	is_redir(char *var)
{
}

// Count redirections by checking if they are valid. Invalid redirections will
// return redir_len = 0. Redirections inside single or double quotes are ignored.
static ssize_t	count_redirs(char *args, t_ptr_tab squote_tab,
							t_ptr_tab dquote_tab)
{
}

static void	search_redir_candidate(t_ptr_tab *var_tab, t_ptr_tab squote_tab,
									t_ptr_tab dquote_tab)
{
}

// Locate every redirection and store its start and end in a pointer table.
// start is a pointer to first char, end is a pointer to next char of last.
// Example:	echo My name is $USER, hello! | cat > file
// 			|                             ||    ||
// 			orig                          start[0]
// 			                               |    ||
// 			                               end[0]|
// 			                                    ||
// 			                                    start[1]
// 			                                     end[1]
ssize_t	locate_redirs(char *args, t_mini *msh)
{
	msh->redir_tab->count = count_redirs(args, *msh->squote_tab,
			*msh->dquote_tab);
	if (msh->redir_tab->count > 0)
	{
		msh->redir_tab = ft_taballoc(msh->redir_tab, args, sizeof(char *));
		if (!msh->redir_tab)
		{
			perror("Error allocating variable pointer table");
			return (-1);
		}
		search_redir_candidate(msh->redir_tab, *msh->squote_tab,
			*msh->dquote_tab);
	}
	if (msh->redir_tab->count < 0)
		perror("Error locating variables");
	return (msh->redir_tab->count);
}
