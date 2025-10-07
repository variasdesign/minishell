/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/07 20:58:16 by varias-c         ###   ########.fr       */
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

# define TABLE_NUM 5

typedef struct s_mini
{
	char		*cwd;
	char		*path;
	int			exit_code;
	t_cmd		*first;
	t_ptr_tab	*redir_tab;
	t_ptr_tab	*squote_tab;
	t_ptr_tab	*dquote_tab;
	t_ptr_tab	*var_tab;
	t_ptr_tab	*word_tab;
}	t_mini;

extern int	g_sig;

char	**split_vars(t_mini	*msh);
char	*expander(char *args, t_mini *msh);
int		exec_input(t_mini *msh);
ssize_t	locate_squotes(char *args, t_ptr_tab *squote_tab);
ssize_t	locate_dquotes(char *args, t_ptr_tab *dquote_tab);
ssize_t	locate_vars(char *args, t_ptr_tab *var_tab, t_ptr_tab squote_tab);
t_mini	*allocate_minishell(void);
void	catch_int(int sig_num);
void	catch_suspend(int sig_num);

#endif
