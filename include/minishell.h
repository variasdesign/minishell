/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/09/30 18:09:55 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char			**args;
	int				pipe_in;
	int				pipe_out;
	char			*heredoc_fd;
	struct s_cmd	*next;
	// TODO: t_redir struct?
}	t_cmd;

typedef struct s_mini
{
	t_list	*env;
	char	*cwd;
	char	*path;
	t_cmd	*first;
	int		exit_code;
}	t_mini;

char	*expander(char *args);
int		exec_input(t_mini *minishell);
int		is_variable(char *var_ptr);
void	parse_input(t_mini *minishell);
void	save_history(t_mini *minishell);
void	show_prompt(t_mini *minishell);
void	signals(t_mini *minishell);

#endif
