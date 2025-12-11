/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/10 20:02:10 by varias-c         ###   ########.fr       */
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
#include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Numbers of pointer tables to initialize
# define TABLE_NUM 5

// Error messages
# define E_ARGS_NOT_TAKEN "This program doesn't take any arguments.\n"
# define E_CHILD_ERR "Children exited with error.\n"
# define E_DUP_FAILURE "Duplication of file descriptors failed: %s\n"
# define E_EXEC_NOT_FOUND "Executable not found in PATH: %s\n"
# define E_EXEC_FAILURE "Children didn't exit correctly.\n"
# define E_FORK_FAILURE "Couldn't fork: %s\n"
# define E_HEREDOC_FAILURE "heredoc couldn't be created or written to.\n"
# define E_INVALID_EXEC "File not found: %s\n"
# define E_INVALID_HERE_DOC "Invalid heredoc delimiter.\n"
# define E_INVALID_PROMPT "Invalid prompt.\n"
# define E_PATH_FAILURE "PATH env not found.\n"
# define E_PIPE_FAILURE "Couldn't create pipes: %s\n"
# define E_QUOTE_PARITY "Invalid number of %c quotes.\n"
# define E_SHELL_PERROR "minishell: %s: %s\n"
# define E_UNREADABLE_INPUT "Input is not readable: %s\n"
# define E_UNWRITABLE_OUTPUT "Output is not writable: %s\n"

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
	char		*input;
	char		*prompt;
	pid_t		*pids;
	t_bool		loop;
	t_list		*cmd_list;
	t_list		*token_list;
	t_ptr_tab	*dquote_tab;
	t_ptr_tab	*redir_tab;
	t_ptr_tab	*squote_tab;
	t_ptr_tab	*var_tab;
	t_ptr_tab	*word_tab;
}	t_mini;

extern volatile sig_atomic_t	g_sig;

char			**split_vars(t_mini *msh);
char			*assemble_prompt(char **env_list, char *prompt);
char			*dup_token_content(t_node *node);
char			*expander(t_mini *msh);
char			*get_env(char **env_list, char *env);
int				exec_cmd_list(t_mini *msh, t_list *cmd_list, char **env);
int				get_exec_path(t_cmd *cmd, char **env);
int				heredoc(char *lim);
int				open_files(t_cmd *cmd, char **env);
int				quote_char(char c);
int				redir_char(char c);
int				redir_start(char *str);
pid_t			fork_and_exec(t_mini *msh, t_node *cmd, char **env);
size_t			count_word_groups(t_list token_list);
size_t			count_word_tokens(t_node *cmd_node);
ssize_t			get_env_index(char **env_list, char *env);
ssize_t			is_redir(char *redir);
ssize_t			locate_quotes(char *args, t_ptr_tab *quote_tab, char q);
ssize_t			locate_redirs(char *args, t_mini *msh);
ssize_t			locate_vars(char *args, t_ptr_tab *var_tab,
					t_ptr_tab squote_tab);
ssize_t			locate_words(char *args, t_mini *msh);
ssize_t			skip_word(char *str, ssize_t *word_len_ptr);
ssize_t			skip_quoted_word(char *str, t_ptr_tab quote_tab,
					ssize_t *word_len_ptr);
ssize_t			validate_quotes(t_ptr_tab *squote_tab, t_ptr_tab *dquote_tab);
t_bool			check_exit(t_cmd *cmd);
t_bool			check_non_word_char(char c);
t_bool			is_redir_type(t_token_type type);
t_bool			is_word_type(t_token_type type);
t_bool			validate_token_list(t_list token_list);
t_list			*lexer(t_mini *msh);
t_list			*parser(t_list *token_list);
t_mini			*allocate_minishell(char **envp);
t_node			*find_token_node(t_node *offset,
					t_token_type type, t_bool last);
t_ptr_tab		*search_quote_candidates(t_ptr_tab *quote_tab, char q);
t_token_type	get_token_type(t_node *token);
t_token_type	find_token_type(char *start, t_token_type prev);
void			child_cleanup_and_exit(t_mini *msh, int exit_code);
void			exec_signal(void);
void			exit_error(char *msg, char *err, int exit_code);
void			free_all(t_mini *msh);
void			free_cmd_list(void *cmd_ptr);
void			free_tables(t_mini *msh, t_bool free_full_table);
void			input_signal(void);
void			interrupt(int signal);
void			print_error(char *msg, char *err);
void			prompt_handler(int signal);
void			quit(int signal);
void			save_word(char *word[2], t_ptr_tab *word_tab, ssize_t i);

// Built-ins
int				builtin_cd(char **args, char ***env);
int				builtin_pwd(void);
int				builtin_exit(char **args);
int				exec_builtin(t_cmd *cmd, char ***env);
int				is_builtin(t_cmd *cmd);

#endif
