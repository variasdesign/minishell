/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:02:37 by varias-c          #+#    #+#             */
/*   Updated: 2024/11/07 18:14:05 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	len = ft_strlen(s1) - 1;
	while (len > start && ft_strchr(set, s1[len]) != NULL)
		len--;
	return (ft_substr(s1, start, len + 1 - start));
}
/*
int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	ft_strtrim(argv[1], argv[2]);
	return (0);
}
*/
