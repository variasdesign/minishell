/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:19:24 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/11 18:35:36 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Placeholder for gdb: "echo jmellado es el \"usuario\" | cat > file" 
// recall locate_quotes
// TODO: Redir and word validation: Prompts can't start or end with a redir,
// and (if I'm not mistaken) there should be more words than redirs.
char	*lexer(char *args, t_mini *msh)
{
	locate_quotes(args, msh->squote_tab, '\'');
	locate_quotes(args, msh->dquote_tab, '\"');
	locate_redirs(args, msh);
	locate_words(args, msh);
	return (args);
}
