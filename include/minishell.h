/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/04 22:43:30 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
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

extern int	g_sig;

char	**locate_vars(char *args, int count);
char	**split_vars(char *args, char **var_table);
char	*expander(char *args);
ssize_t	count_variables(char *args);
int		exec_input(t_mini *minishell);
ssize_t	is_variable(char *var_ptr);
void	catch_int(int sig_num);
void	catch_suspend(int sig_num);

#endif
