/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/28 18:32:06 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Segregate in different headers
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

typedef enum e_token_type
{
	TOKEN_NULL,
	TOKEN_WORD_CMD,
	TOKEN_WORD_ARG,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*start;
	char			*end;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
}	t_redir;

typedef struct s_cmd
{
	char	**args;
	t_list	*redir_list;
	t_bool	pipe_in;
	t_bool	pipe_out;
}	t_cmd;

# define TABLE_NUM 5

typedef struct s_mini
{
	char		*cwd;
	char		*path;
	int			exit_code;
	char		*heredoc_fd;
	t_list		*cmd_list;
	t_ptr_tab	*redir_tab;
	t_ptr_tab	*squote_tab;
	t_ptr_tab	*dquote_tab;
	t_ptr_tab	*var_tab;
	t_ptr_tab	*word_tab;
}	t_mini;

extern int	g_sig;

char			**split_vars(t_ptr_tab *var_tab);
char			*expander(char *args, t_ptr_tab *squote_tab,
					t_ptr_tab *dquote_tab, t_ptr_tab *var_tab);
char			*token_content(t_node *node);
int				exec_input(t_mini *msh);
int				quote_char(char c);
int				redir_char(char c);
int				redir_start(char *str);
size_t			count_word_groups(t_list token_list);
size_t			count_word_tokens(t_node *cmd_node);
ssize_t			is_redir(char *redir);
ssize_t			locate_quotes(char *args, t_ptr_tab *quote_tab, char q);
ssize_t			locate_redirs(char *args, t_mini *msh);
ssize_t			locate_vars(char *args, t_ptr_tab *var_tab,
					t_ptr_tab squote_tab);
ssize_t			locate_words(char *args, t_mini *msh);
ssize_t			validate_quotes(t_ptr_tab *squote_tab, t_ptr_tab *dquote_tab);
t_bool			is_redir_type(t_token_type type);
t_bool			is_word_type(t_token_type type);
t_bool			validate_token_list(t_list token_list);
t_list			*lexer(char *args, t_mini *msh);
t_list			*parser(t_list *token_list);
t_mini			*allocate_minishell(void);
t_node			*find_token_node(t_node *offset, t_token_type type, t_bool last);
t_ptr_tab		*search_quotes_candidates(t_ptr_tab *quote_tab, char q);
t_token_type	get_token_type(t_node *token);
void			catch_int(int sig_num);
void			catch_suspend(int sig_num);

#endif
