/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:33:57 by varias-c          #+#    #+#             */
/*   Updated: 2024/10/28 18:57:18 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	str_len;
	char			*str;
	size_t			i;
	size_t			j;

	if (!s1 || !s2)
		return (NULL);
	str_len = ft_strlen(s1) + ft_strlen (s2) + 1;
	str = ft_calloc(str_len, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	return (str);
}
