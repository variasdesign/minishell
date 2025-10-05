# Notes

## Prompt processing
### Expander
- The expander does variable expansion and single quote handling.
- Perhaps it would need to handle double quoting too, since quoting an empty variable produces a single space, while an unquoted empty variable produces no characters.

### Lexer
- The lexer does categorization (also called tokenization) of arguments, taking into account special characters involved in process piping or redirections. Considering that double quotes escape everything but variables, I think double quotes should be handled by the lexer, since variables will be expanded by the expander.
