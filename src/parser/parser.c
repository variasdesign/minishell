/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:09 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/23 17:56:14 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Parser: Iterate args while searching all pointer tables, then link each
// pointer table occurrence to obtain the command table
// TODO: Redir and word validation: Prompts can't start or end with a redir,
// and (if I'm not mistaken) there should be more words than redirs.
t_cmd	*parser(t_list *token_list)
{
	(void)token_list;
	return (NULL);
}
