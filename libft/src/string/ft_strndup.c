/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 19:10:30 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/03 19:17:16 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	const size_t	s_len = ft_strlen(s);
	char			*dup;

	if (n > s_len)
		dup = ft_calloc(s_len + 1, sizeof(char));
	else
		dup = ft_calloc(n + 1, sizeof(char));
	if (!dup)
		return (NULL);
	if (n > s_len)
		dup = ft_memcpy(dup, s, s_len);
	else
		dup = ft_memcpy(dup, s, n);
	return (dup);
}
