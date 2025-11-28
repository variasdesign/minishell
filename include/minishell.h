/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:35:35 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Segregate in different headers
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>

// Numbers of pointer tables to initialize
# define TABLE_NUM 5

// Error messages
# define E_CHILD_ERR "Children exited with error.\n"
# define E_EXEC_FAILURE "Execution failed: %s\n"
# define E_FILE_FAILURE "Opening of redirections failed: %s\n"
# define E_DUP_FAILURE "Duplication of file descriptors failed: %s\n"
# define E_EXEC_NOT_FOUND "Executable not found in PATH: %s\n"
# define E_FORK_FAILURE "Couldn't fork: %s\n"
# define E_INVALID_EXEC "File not found: %s\n"
# define E_INVALID_PROMPT "Invalid prompt.\n"
# define E_PATH_FAILURE "PATH env not found.\n"
# define E_PIPE_FAILURE "Couldn't create pipes: %s\n"
# define E_UNREADABLE_INPUT "Input is not readable: %s\n"
# define E_UNWRITABLE_OUTPUT "Output is not writable: %s\n"
# define E_HEREDOC_FAILURE "heredoc couldn't be created or written to.\n"
# define E_INVALID_HERE_DOC "Invalid heredoc delimiter.\n"

typedef enum e_token_type
{
	TOKEN_NULL,
	TOKEN_WORD_CMD,
	TOKEN_WORD_ARG,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_IN_ALL,
	TOKEN_REDIR_OUT_ALL,
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
	int		fd_in;
	int		fd_out;
	t_bool	pipe_from;
	t_bool	pipe_to;
}	t_cmd;

typedef struct s_mini
{
	char		**env;
	char		*cwd;
	char		*path;
	int			exit_code;
	t_bool		loop;
	t_list		*cmd_list;
	t_ptr_tab	*dquote_tab;
	t_ptr_tab	*redir_tab;
	t_ptr_tab	*squote_tab;
	t_ptr_tab	*var_tab;
	t_ptr_tab	*word_tab;
}	t_mini;

extern int	g_sig;

char			**split_vars(t_ptr_tab *var_tab);
char			*expander(char *args, t_ptr_tab *squote_tab,
					t_ptr_tab *dquote_tab, t_ptr_tab *var_tab);
char			*token_content(t_node *node);
char			*get_env(char **env_list, char *env);
int				check_fd_errors(t_cmd *cmd);
int				exec_input(t_list *cmd_list, char **env);
int				quote_char(char c);
int				redir_char(char c);
int				redir_start(char *str);
int				open_files(t_cmd *cmd, int fd[2]);
pid_t			fork_and_exec(t_node *cmd, char **env);
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
t_mini			*allocate_minishell(char **envp);
t_node			*find_token_node(t_node *offset,
					t_token_type type, t_bool last);
t_ptr_tab		*search_quotes_candidates(t_ptr_tab *quote_tab, char q);
t_token_type	get_token_type(t_node *token);
void			catch_int(int sig_num);
void			catch_suspend(int sig_num);
void			exit_error(char *msg, char *err, int exit_code);
void			free_all(t_mini *msh);
void			print_error(char *msg, char *err);

#endif
