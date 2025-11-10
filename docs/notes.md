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
