/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/10 13:15:46 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC
} t_token_type;

<<<<<<< HEAD



	typedef struct s_cmd
=======
typedef struct s_redir
{
	int		redir_type;
	char	*file;
}	t_redir;

typedef struct s_cmd
>>>>>>> 4351e33b4e7a56c46ccc32e06614b4a2dc3fe4b1
{
	char			**args;
	t_redir			*redirections;
	int				pipe_in;
	int				pipe_out;
	char			*heredoc_fd;
	struct s_cmd	*next;
<<<<<<< HEAD
	// TODO: t_redir struct?
}					t_cmd;
=======
}	t_cmd;
>>>>>>> 4351e33b4e7a56c46ccc32e06614b4a2dc3fe4b1

# define TABLE_NUM 5

typedef struct s_mini
{
<<<<<<< HEAD
	char			*cwd;
	char			*path;
	int				exit_code;
	t_cmd			*first;
	t_ptr_tab		*redir_tab;
	t_ptr_tab		*squote_tab;
	t_ptr_tab		*dquote_tab;
	t_ptr_tab		*var_tab;
	t_ptr_tab		*word_tab;
}					t_mini;
=======
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
>>>>>>> 4351e33b4e7a56c46ccc32e06614b4a2dc3fe4b1

extern int			g_sig;

t_ptr_tab			*search_quotes_candidates(char *args, t_ptr_tab *quote_tab,
						char q);
char				**split_vars(t_mini *msh);
char				*expander(char *args, t_mini *msh);
int					is_redir_char(char c);
int					is_redir_start(char *str);
char				*process_redir(char *str, int redir_len, t_mini *msh, ssize_t *count);
int					is_inside_quotes(char *pos, t_mini *msh);
int					exec_input(t_mini *msh);
ssize_t				locate_quotes(char *args, t_ptr_tab *quote_tab, char q);
ssize_t				locate_vars(char *args, t_ptr_tab *var_tab,
						t_ptr_tab squote_tab);
ssize_t				validate_quotes(t_ptr_tab *squote_tab,
						t_ptr_tab *dquote_tab);
t_mini				*allocate_minishell(void);
void				catch_int(int sig_num);
void				catch_suspend(int sig_num);

#endif
