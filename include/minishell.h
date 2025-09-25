/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/09/15 16:32:47 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_mini
{
	t_list		*env;
}	t_mini;

int	g_sig;

void	show_prompt(t_mini *minishell);
void	read_input(t_mini *minishell);
void	parse_input(t_mini *minishell);
void	exec_input(t_mini *minishell);
void	signals(t_mini *minishell);
void	save_history(t_mini *minishell);

#endif
