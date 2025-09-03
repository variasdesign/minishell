# minishell
## Description
Write a program that emulates a shell.

## Scope
1. Parse user environment variables
2. Show a prompt, preferably with user and pwd printed
3. Receive user input (readline?)
4. Parse user input
	- Not interpret unclose quotes or \ or ;
	- Handle single quotes (')
	- Handle double quotes (")
	- Redirections
		- < input
		- \> output
		- << heredoc
		- \>\> output append
	- Pipes
	- Environment variables ($VARIABLE)
	- Exit code ($?)
	- Ctrl-C (SIGINT), Ctrl-D (exit) & Ctrl-\ (???)
		- Non-interactive mode
		- Interactive mode
	- Built-ins:
		- echo -n
		- cd <relative or absolute path>
		- pwd
		- export
		- unset
		- env
		- exit
5. Execute parsed input
	- Search for executables in PATH
6. Interpret any signals sent to the global signal variable (to be researched)
7. Save input to history
8. Display a new prompt

## Requirements
- The project should follow bash design and reference (https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)
- Allowed functions: readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
- Libft allowed
