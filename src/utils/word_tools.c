#include "minishell.h"

static ssize_t	get_word_len(char *word)
{
	int	len;

	len = 0;
	while (word[len] && !ft_isspace(word[len]) && !is_redir_char(word[len]))
		len++;
	return (len);
}

// Skip whitespace characters
static char	*skip_whitespace(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

// Check if position is inside quotes (protected from tokenization)
int	is_inside_quotes(char *pos, t_mini *msh)
{
	// If ft_tabfind returns >= 0, it means the position is inside quotes
	return (ft_tabfind(pos, *msh->squote_tab) >= 0 || ft_tabfind(pos,
			*msh->dquote_tab) >= 0);
}


// Process regular word and advance pointer
static char	*process_word(char *str, ssize_t *count)
{
	int	word_len;

	word_len = get_word_len(str);
	if (word_len > 0)
	{
		(*count)++;  // Always count text as word
		return (str + word_len);
	}
	return (str + 1);  // Skip single character if not part of word
}