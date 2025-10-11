#include "minishell.h"

int	is_redir_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int is_redir(char *str)
{
    size_t len;

    len = 0;
    if (str[len] == '|' && ft_isspace(str[len + 1]))
        return (++len);
    while (str[len] == '<' || str[len] == '>' && len < 2)
    {
       len++;
    }
    if (len > 1)
        return (0);
    return (len + 1);
}
// Process redirection operator and advance pointer
char	*process_redir(char *str, int redir_len, t_mini *msh, ssize_t *count)
{
	if (is_inside_quotes(str, msh))
	{
		// Operator inside quotes = counts as word
		(*count)++;
	}
	// Operator outside quotes = skip, don't count
	return (str + redir_len);
}

// Check if current position starts with a redirection operator
int	is_redir_start(char *str)
{
	if (!str || !*str)
		return (0);
	
	// Check for double operators first
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	
	// Check for single operators
	if (str[0] == '<' || str[0] == '>' || str[0] == '|')
		return (1);
	
	return (0);
}