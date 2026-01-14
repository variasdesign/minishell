/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_locate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:24:09 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 18:44:19 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// We first check if the prospective redirection is inside quotes or was a now
// expanded variable, incrementing the count if neither is true.
static char	*check_redir_inside_tables(char *redir_can, t_mini *msh,
								ssize_t *count)
{
	ssize_t	redir_len;
	ssize_t	ptr_index[3];

	ptr_index[SQUOTE] = ft_tabfind(redir_can, *msh->squote_tab, f);
	ptr_index[DQUOTE] = ft_tabfind(redir_can, *msh->dquote_tab, f);
	ptr_index[VAR] = ft_tabfind(redir_can, *msh->var_tab, t);
	if (ptr_index[SQUOTE] < 0 && ptr_index[DQUOTE] < 0 && ptr_index[VAR] < 0)
	{
		redir_len = is_redir(redir_can);
		*count += redir_len > 0;
		redir_can = redir_strchr(redir_can + redir_len);
	}
	else if (ptr_index[SQUOTE] >= 0)
		redir_can = redir_strchr(msh->squote_tab->end[ptr_index[SQUOTE]]);
	else if (ptr_index[DQUOTE] >= 0)
		redir_can = redir_strchr(msh->dquote_tab->end[ptr_index[DQUOTE]]);
	else if (ptr_index[VAR] >= 0)
		redir_can = redir_strchr(msh->var_tab->end[ptr_index[VAR]]);
	return (redir_can);
}

// Count redirections by checking if they are valid. Invalid redirections will
// return redir_len = 0. Redirs inside single or double quotes are ignored.
static ssize_t	count_redirs(char *args, t_mini *msh)
{
	ssize_t	count;
	char	*redir_can;

	count = 0;
	redir_can = redir_strchr(args);
	while (redir_can)
		redir_can = check_redir_inside_tables(redir_can, msh, &count);
	return (count);
}

static char	*insert_redir_into_tab(char *redir_can, t_ptr_tab *redir_tab,
									ssize_t i)
{
	ssize_t	redir_len;

	redir_len = is_redir(redir_can);
	if (redir_len)
	{
		redir_tab->start[i] = redir_can;
		redir_tab->end[i] = redir_can + redir_len;
	}
	return (redir_strchr(redir_can + redir_len));
}

// Look for redirection candidates to insert into the table by checking
// if they are not inside quotes or if they are now expanded variables,
// which doesn't count as redirections.
static ssize_t	search_redir_candidates(t_ptr_tab *redir_tab,
			t_ptr_tab squote_tab, t_ptr_tab dquote_tab, t_ptr_tab var_tab)
{
	ssize_t	ptr_index[3];
	char	*redir_can;
	ssize_t	i;

	redir_can = redir_strchr(redir_tab->orig);
	i = 0;
	while (i < redir_tab->count && redir_can)
	{
		ptr_index[SQUOTE] = ft_tabfind(redir_can, squote_tab, f);
		ptr_index[DQUOTE] = ft_tabfind(redir_can, dquote_tab, f);
		ptr_index[VAR] = ft_tabfind(redir_can, var_tab, t);
		if (ptr_index[SQUOTE] < 0
			&& ptr_index[DQUOTE] < 0
			&& ptr_index[VAR] < 0)
			redir_can = insert_redir_into_tab(redir_can, redir_tab, i++);
		else if (ptr_index[SQUOTE] >= 0)
			redir_can = redir_strchr(squote_tab.end[ptr_index[SQUOTE]]);
		else if (ptr_index[DQUOTE] >= 0)
			redir_can = redir_strchr(dquote_tab.end[ptr_index[DQUOTE]]);
		else if (ptr_index[VAR] >= 0)
			redir_can = redir_strchr(var_tab.end[ptr_index[VAR]]);
	}
	return (i);
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
	msh->redir_tab->count = count_redirs(args, msh);
	if (msh->redir_tab->count > 0)
	{
		msh->redir_tab = ft_taballoc(msh->redir_tab, args, sizeof(char *));
		if (!msh->redir_tab)
		{
			ft_printf(2, "Error allocating redirection pointer table: %s",
				strerror(errno));
			return (-1);
		}
		if (search_redir_candidates(msh->redir_tab, *msh->squote_tab,
				*msh->dquote_tab, *msh->var_tab) != msh->redir_tab->count)
		{
			ft_printf(2, "Error locating redirections.\n");
			return (-1);
		}
	}
	if (msh->redir_tab->count < 0)
		ft_printf(2, "Error locating redirections.\n");
	return (msh->redir_tab->count);
}
