/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:23:18 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/03 17:59:45 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	word_count(const char *s, const char c)
{
	size_t	i;
	int		count;
	int		inside_word;

	i = 0;
	count = 0;
	inside_word = 0;
	while (s[i])
	{
		if (s[i] != c && !inside_word)
		{
			count++;
			inside_word = 1;
		}
		else if (s[i] == c)
			inside_word = 0;
		i++;
	}
	return (count);
}

static unsigned int	calculate_word_index(const char *s, size_t char_i, char c)
{
	unsigned int	word_len;

	word_len = 0;
	while (*(s + char_i) != c && *(s + char_i) != '\0')
	{
		char_i++;
		word_len++;
	}
	return (word_len);
}

char	**ft_split(const char *s, char c)
{
	const unsigned int		count = word_count(s, c);
	unsigned int			word_i;
	unsigned int			word_len;
	size_t					char_i;
	char					**split_str;

	if (!s)
		return (NULL);
	split_str = ft_calloc(count + 1, sizeof(char *));
	if (!split_str)
		return (NULL);
	word_i = -1;
	char_i = 0;
	while (++word_i < count)
	{
		while (s[char_i] == c)
			char_i++;
		word_len = calculate_word_index(s, char_i, c);
		split_str[word_i] = ft_substr(s, char_i, word_len);
		if (!split_str[word_i])
			return ((char **)ft_freematrix((void **)split_str));
		char_i = char_i + word_len;
	}
	return (split_str);
}

/* int	main(int argc, char **argv) */
/* { */
/*  	char c = 0; */
/*  	if (argc != 2) */
/*  		return (1); */
/*  	ft_split(argv[1], c); */
/*  	return (0); */
/* } */
