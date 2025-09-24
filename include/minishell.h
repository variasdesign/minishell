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

typedef struct s_history
{
}	t_history;

typedef struct s_signal
{
	int	sig;
}	t_signal;

typedef struct s_mini
{
	char		**env;
	t_signal	sig;
	t_history	his;
}	t_mini;

void init_struct(t_mini *minishell, char **envp);
void show_prompt(t_mini *minishell);
void read_input(t_mini *minishell);
void parse_input(t_mini *minishell);
void exec_input(t_mini *minishell);
void signals(t_mini *minishell);
void save_history(t_mini *minishell);

#endif
