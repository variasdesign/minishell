# Notes

## Prompt processing
Most of the prompt processing deals with string classification and manipulation. Thus the use of pointer tables, which allow us to store pointers (start and end) to memory addresses containing substrings of the original string. Pointer tables can be reused since the three parts of the prompt processing stage work with certain common data.

### Structure
- Preprocessing
- Expander
- Lexer
- Parser.

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
