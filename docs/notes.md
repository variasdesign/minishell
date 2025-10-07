# Notes
## Prompt processing
### Structure
- Expander
- Lexer
- Parser.
- Most of the prompt processing deals with string classification and manipulation. Thus the use of pointer tables, which allow us to store pointers (start and end) to memory addresses containing substrings of the original string. Pointer tables can be reused since the three parts of the prompt processing stage work with certain common data.

### Expander
- The expander does variable expansion and single quote handling.
- Perhaps it would need to handle double quoting too, since quoting an empty variable produces a single space, while an unquoted empty variable produces no characters.
- The expander needs three pointer tables:
	- Single quote table: single-quoted variables must not be expanded.
	- Double quote table

### Lexer
- The lexer does categorization (also called tokenization) of arguments, taking into account special characters involved in process piping or redirections. Considering that double quotes escape everything but variables, I think double quotes should be handled by the lexer, since variables will be expanded by the expander.
