# Notes

## Prompt processing
Most of the prompt processing deals with string classification and manipulation. Thus the use of pointer tables, which allow us to store pointers (start and end) to memory addresses containing substrings of the original string. Pointer tables can be reused since the three parts of the prompt processing stage work with certain common data.

### Structure
- Preprocessing
- Expander
- Lexer
- Parser

### Preprocessing
- Quotes have to be validated. That is, we naively count all present quotes, store in pointer tables and evaluate if they're valid quotes. An example of needed validation is interleaved or nested quotes: '"$USER'" "'$USER"' "'$USER'" '"$USER"'. This string contains valid quoting, but since some of them are inside other quote range, they are taken as literal and thus must not be interpreted.
- Quote validation needs two pointer tables:
	- Single quote table.
	- Double quote table.
- Quotes which are invalidated must be removed from the pointer tables, its space filled by next quotes (if any). This also means that we can invalidate one quote character, or pairs of quotes. An odd number of quotes, single or double, is considered an invalid prompt, but invalidation of quotes will alter the quote count, making an apparent valid prompt invalid and vice versa.
- Good string to test proper quote validation: `echo    0'"dq_in_sq"'_    1"'sq_in_dq'"_    2''twice_sq''_    3""twice_dq""_    4"'inter_dq_lead"'_    5'"inter_sq_lead'"_`

### Expander
- The expander does variable expansion and single quote handling.
- Perhaps it would need to handle double quoting too, since quoting an empty variable produces a single space, while an unquoted empty variable produces no characters.

### Lexer
- The lexer does categorization (also called tokenization) of arguments, taking into account special characters involved in process piping or redirections. Considering that double quotes escape everything but variables, I think double quotes should be handled by the lexer, since variables will be expanded by the expander.
- The lexer generates a linked token list, with the following struct per node:
	- Token type
	- Start and end of token (char *)
- Words are classified by whitespace, but quoting will agglomerate words, even if they are separated by whitespace (except newline).

### Parser
- The parser receives the token list from the lexer. There are two approaches to parsing the token list:
	- AST: More involved and complex, but needed for bonus.
	- Plain-old parsing: If bonus is not needed, prompt can be processed from left to right:
		- Redirections:
			- Input file (`< file`), output file by replacement (`> file`) and output file by appending (`>> file`).
				- Files for input redirection must exist.
				- Files for output redirection shall not exist, but must be created if they don't.
					- Files already existing but used with `>` will be truncated with `O_TRUNC`.
					- Files already existing but used with `>>` will be appended with `O_APPEND`.
			- There can be any number of redirections of each type, but only the rightmost one will be taken into account.
			- Redirections must be followed by a word. The word is interpreted as the filename in the redirection, and after being used as argument, it's removed from the token list.
			- Both output tokens (`> and >>`) count as one type. That is, if `>> file` is specified first, followed by `> file`, `file` will be closed and opened again with `O_TRUNC`. Doesn't matter if filenames are different, only the last specified input or output file descriptor is taken into account.
				- https://stackoverflow.com/questions/20081653/two-redirection-operators-in-one-command#20081848
		- Pipes:
			- Output of command becomes input of next command (`cmd1 | cmd2`).
			- Pipes must be followed and preceded by a word. That also means that the prompt can't start or end with a pipe.
		- Heredoc:
			- Input is taken from the prompt itself, pressing newline (⏎) no longer sends the prompt. Instead, a delimiter is specified and more lines can be fed to the input until the delimiter is found **solely** in a line (<< DELIMITER).
			-	```
				cat << EOF
				this is
				some multine input!
				this line won't stop heredoc EOF
				but the following one will:
				EOF
				```
		- Words:
			- Words are processed as is, with no special consideration. Words used as arguments for redirections will be removed before words are parsed, and thus shouldn't pose an issue.
			- Words are to be classified in groups, being the lead word the command name, and successive words its arguments.
				- Groups of words are separated by pipes or newline, but not redirections.
				- Further division on the word token classification can help with parsing commands or arguments:
					- `TOKEN_WORD_CMD`
					- `TOKEN_WORD_ARG`

- After validating and parsing the token list, a command linked list is assembled, containing the following:
	- An 2D char array containing the command and its arguments.
	- A redirection linked list with its node containing the redirection type and the filename.
	- A input file descriptor.
	- A output file descriptor.
	- A heredoc filename.

## Execution

### Structure

- Exec receives a linked node list from parser containing at least one t_cmd. This struct contains information about the command to execute, a t_redir struct containing redir information (if any) and booleans as flags indicating if there's is any ingoing or outgoing pipe.
- Exec iterates through this list, executing each command with its respective arguments by forking and then capturing its file descriptors to redirect input or output to or from the command.
	- If the list contains a single element, that means that the user provided only a single command, and thus we only need to fork and execve.
	- If the list contains more than one element, that means that the user provided multiple commands chained by pipes, and thus we have to fork, execute and pipe each command until the end of the list.

### Pipex logic
1. Pipex starts by checking arguments and its number, but minishell should take care of this beforehand.
2. here_doc is checked by using strncmp and finding here_doc string in first argument. In the case of minishell, we should check if the << redirect is present and the parser should launch the here_doc logic.
3. Next, checks for number of arguments and if there's extra arguments needed for here_doc, but again, this is checked by parser.
4. Pipex initialization where argc and environment is passed to pipex struct, but this is taken care of by minishell. Then, files are opened. Again, minishell does this.
5. Finally, children processes are deployed:
	- Number of commands is calculated from an arithmetic formula. This is not needed in minishell because we have the length of the command list.
	- pid_t array is initialized with number of commands.
	- For each command, a fork_and_exec is called, except for the last one, which needs every file descriptor closed.
	- Then, parent waits for children to finish executing, then disassembles itself and return the exit status of the last process of the pipe chain.
	- Both children and parent enter fork_and_exec, and pipe() is called. The two file descriptors pipe returns are needed in both children and parent: the parent needs it to pass it to the next command, while the children needs it to write to it.
	- fork() is called and the parent close the writing file descriptor of the pipe, as well as its internal input file descriptor, which is then replaced by the reading part of the pipe, making it ready for reading for the next command.
	- Conversely, the children enters child_process, inside which the reading part of the pipe is closed, because pipex passes the input file descriptor, where it may be a input file from a redirector or a reading part of a pipe from a previous command.
	- The children then duplicate the received file descriptors into the future program's input and output file descriptors, then closes the respective source file descriptors.
	- Finally, exec_wrapper is called, where we obtain the arguments from the command to execute, as well as validate if the executable exists, is readable and is executable. This part should be checked either by the parser or the executor in minishell.

- Another thing to take into account is how the pipex structure translates into the minishell structure, because the pipex structure is designed for one-time execution whenever the program is called.

### Execution order
1. Allocate a pid array and iterate over it, calling fork_and_exec and iterating again calling waitpid.
2. If cmd->pipe_to = 1, it means that it must pipe its output to another command, and thus call pipe(fd) and store the generated pipe fds into an int array of length 2.
3. Fork:
	a. Child:
		1. If there are redirections, try to open their paths and assign corresponding file descriptors to cmd->fd_in and cmd->fd_in, respectively. If instead of redirections, cmd->pipe_from or cmd->pipe_to are true, assign the pipe fds respectively.
		2. Duplicate cmd->fd_in and cmd->fd_out into the child's STDIN_FILENO and STDOUT_FILENO. If there are no redirections or pipes, meaning that cmd->fd_in is already equal to STDIN_FILENO and cmd->fd_out is already equal to STDOUT_FILENO, dup2 does nothing and returns the fd. 
		3. Check if cmd->fd_in or cmd->fd_out were changed from their default values and close the file descriptors if not.
		4. Call exec_wrapper, which checks the executable against PATH and launches the executable.
	b. Parent: 
		1. Close writing end of pipe and pass reading end to the fd_in of the next command.
		2. Return pid of fork for waitpid.

