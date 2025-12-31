/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_locate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:24:09 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/15 19:57:45 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*redir_strchr(char *args)
{
	char	*pipe;
	char	*in;
	char	*out;

	pipe = ft_strchr(args, '|');
	in = ft_strchr(args, '<');
	out = ft_strchr(args, '>');
	if (pipe && (!in || pipe < in) && (!out || pipe < out))
		return (pipe);
	else if (in && (!pipe || in < pipe) && (!out || in < out))
		return (in);
	else if (out && (!pipe || out < pipe) && (!in || out < in))
		return (out);
	return (NULL);
}

// Count redirections by checking if they are valid. Invalid redirections will
// return redir_len = 0. Redirs inside single or double quotes are ignored.
static ssize_t	count_redirs(char *args, t_ptr_tab squote_tab,
								t_ptr_tab dquote_tab, t_ptr_tab var_tab)
{
	ssize_t	count;
	ssize_t	redir_len;
	ssize_t	ptr_index[3];
	char	*redir_can;

	count = 0;
	redir_can = redir_strchr(args);
	while (redir_can)
	{
		ptr_index[SQUOTE] = ft_tabfind(redir_can, squote_tab, f);
		ptr_index[DQUOTE] = ft_tabfind(redir_can, dquote_tab, f);
		ptr_index[VAR] = ft_tabfind(redir_can, var_tab, t);
		if (ptr_index[SQUOTE] < 0 && ptr_index[DQUOTE] < 0 && ptr_index[VAR] < 0)
		{
			redir_len = is_redir(redir_can);
			count += redir_len > 0;
			redir_can = redir_strchr(redir_can + redir_len);
		}
		else if (ptr_index[SQUOTE] >= 0)
			redir_can = redir_strchr(squote_tab.end[ptr_index[SQUOTE]]);
		else if (ptr_index[DQUOTE] >= 0)
			redir_can = redir_strchr(dquote_tab.end[ptr_index[DQUOTE]]);
		else if (ptr_index[VAR] >= 0)
			redir_can = redir_strchr(var_tab.end[ptr_index[VAR]]);
	}
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

static void	search_redir_candidates(t_ptr_tab *redir_tab, t_ptr_tab squote_tab,
									t_ptr_tab dquote_tab, t_ptr_tab var_tab)
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
		if (ptr_index[SQUOTE] < 0 && ptr_index[DQUOTE] < 0 && ptr_index[VAR] < 0)
			redir_can = insert_redir_into_tab(redir_can, redir_tab, i++);
		else if (ptr_index[SQUOTE] >= 0)
			redir_can = redir_strchr(squote_tab.end[ptr_index[SQUOTE]]);
		else if (ptr_index[DQUOTE] >= 0)
			redir_can = redir_strchr(dquote_tab.end[ptr_index[DQUOTE]]);
		else if (ptr_index[VAR] >= 0)
			redir_can = redir_strchr(var_tab.end[ptr_index[VAR]]);
	}
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
// FIX: Add error checking to search_redir_candidates (see word_locate.c)
ssize_t	locate_redirs(char *args, t_mini *msh)
{
	msh->redir_tab->count = count_redirs(args, *msh->squote_tab,
			*msh->dquote_tab, *msh->var_tab);
	if (msh->redir_tab->count > 0)
	{
		msh->redir_tab = ft_taballoc(msh->redir_tab, args, sizeof(char *));
		if (!msh->redir_tab)
		{
			perror("Error allocating redirection pointer table");
			msh->redir_tab->count = -1;
		}
		else
			search_redir_candidates(msh->redir_tab, *msh->squote_tab,
				*msh->dquote_tab, *msh->var_tab);
	}
	if (msh->redir_tab->count < 0)
		printf("Error locating redirections.\n");
	return (msh->redir_tab->count);
}
