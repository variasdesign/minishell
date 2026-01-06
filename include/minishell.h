/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:21 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/06 11:51:19 by ttonchak         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Numbers of pointer tables to initialize
# define TABLE_NUM 5

// Error messages
# define E_ARGS_NOT_TAKEN "This program doesn't take any arguments.\n"
# define E_CHILD_ERR "Children exited with error.\n"
# define E_DUP_FAILURE "Duplication of file descriptors failed: %s\n"
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

typedef enum e_builtin
{
	CMD_NULL,
	CMD_CD,
	CMD_ECHO,
	CMD_ENV,
	CMD_EXIT,
	CMD_EXPORT,
	CMD_PWD,
	CMD_UNSET,
}	t_builtin;

enum e_ptr_index
{
	SQUOTE,
	DQUOTE,
	VAR,
};

typedef struct s_token
{
	t_token_type	type;
	char			*start;
	char			*end;
	t_bool			rewritten;
}	t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

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
	char		*input;
	char		*prompt;
	pid_t		*pids;
	t_bool		*expanded_vars;
	t_bool		loop;
	t_bool		cmd_since_last_pipe;
	t_bool		heredoc_expand;
	t_list		*cmd_list;
	t_list		*env;
	t_list		*token_list;
	t_ptr_tab	*dquote_tab;
	t_ptr_tab	*redir_tab;
	t_ptr_tab	*squote_tab;
	t_ptr_tab	*var_tab;
	t_ptr_tab	*word_tab;
}	t_mini;

extern volatile sig_atomic_t	g_sig;

char			**split_vars(t_mini *msh);
char			**reassemble_env(t_list *env_list);
char			*assemble_prompt(t_list *env, char *prompt);
char			*dup_token_content(t_node *token_node);
char			*get_redir_path(t_node *redir_node);
char			*expander(t_mini *msh);
char			*skip_redir(char *str, t_ptr_tab redir_tab);
int				exec_cmd_list(t_mini *msh, t_list *cmd_list, t_list *env);
int				get_exec_path(t_cmd *cmd, t_list *env_list);
int				heredoc(char *lim, t_list *env_list, t_bool expand_vars);
int				open_files(t_cmd *cmd, t_list *env_list, t_bool expand_vars);
int				quote_char(char c);
int				redir_char(char c);
int				redir_start(char *str);
pid_t			fork_and_exec(t_mini *msh, t_node *cmd, t_list *env_list);
size_t			count_word_groups(t_list token_list);
size_t			count_word_tokens(t_node *cmd_node);
ssize_t			get_env_index(t_list *env_list, char *var);
ssize_t			is_redir(char *redir);
ssize_t			is_variable(char *var);
ssize_t			locate_quotes(char *args, t_ptr_tab *quote_tab, char q);
ssize_t			locate_redirs(char *args, t_mini *msh);
ssize_t			locate_vars(char *args, t_ptr_tab *var_tab,
					t_ptr_tab squote_tab);
ssize_t			locate_words(char *args, t_mini *msh);
ssize_t			skip_word(char *str, ssize_t *word_len_ptr,
					t_ptr_tab redir_tab);
ssize_t			skip_quoted_word(char *str, t_ptr_tab quote_tab,
					ssize_t *word_len_ptr);
ssize_t			validate_quotes(t_ptr_tab *squote_tab, t_ptr_tab *dquote_tab);
ssize_t			validate_vars(t_ptr_tab *var_tab, t_ptr_tab *dquote_tab,
					t_ptr_tab *squote_tab);
t_bool			check_exit(t_cmd *cmd);
t_bool			is_redir_type(t_token_type type);
t_bool			is_word_type(t_token_type type);
t_bool			validate_token_list(t_list token_list);
t_env			*get_env(t_list *env_list, char *var);
t_env			*get_env_pos(t_list *env_list, ssize_t pos);
t_list			*lexer(t_mini *msh);
t_list			*modify_env(t_list *env_list, char *var, char *new_value);
t_list			*parser(t_list *token_list);
t_mini			*allocate_minishell(char **envp);
t_node			*find_token_node(t_node *offset,
					t_token_type type, t_bool last);
t_node			*add_env(t_list *env_list, char *var, char *value);
t_node			*get_env_node(t_list *env_list, char *var);
t_token_type	get_token_type(t_node *token);
t_token_type	find_token_type(char *start, t_token_type prev,
					t_bool *cmd_since_last_pipe, t_ptr_tab redir_tab);
void			child_cleanup(t_mini *msh, int exit_code);
void			exec_signal(void);
void			exit_error(char *msg, char *err, int exit_code);
void			free_all(t_mini *msh);
void			free_cmd_list(void *cmd_ptr);
void			free_redir_list(void *redir_ptr);
void			free_tables(t_mini *msh, t_bool free_full_table);
void			input_signal(void);
void			interrupt(int signal);
void			print_error(char *msg, char *err);
void			prompt_handler(int signal);
void			quit(int signal);
void			save_word(char *word[2], t_ptr_tab *word_tab, ssize_t i);

// Built-ins
int				builtin_cd(char **args, t_list *env_list);
int				builtin_pwd(void);
int				builtin_echo(char **args);
int				builtin_env(char **args, t_list *env_list);
int				builtin_export(char **args, t_list *env_list);
int				builtin_unset(char **args, t_list *env_list);
int				builtin_exit(char **args, t_bool *loop);
t_env			*create_env_var(char *key, char *value);
int				exec_builtin(t_cmd *cmd, t_list *env_list, t_bool *loop);
int				exec_single_builtin(t_cmd *cmd, t_list *env_list, t_bool *loop, t_bool heredoc_expand);
t_builtin		is_builtin(t_cmd *cmd);

#endif
