/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:59:06 by varias-c          #+#    #+#             */
/*   Updated: 2024/10/07 19:11:59 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1 = (unsigned char *)s1;
	const unsigned char	*str2 = (unsigned char *)s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

ssize_t	ft_sstcmp(const void *s1, const void *s2)
{
	const ssize_t	*n1 = (ssize_t *)s1;
	const ssize_t	*n2 = (ssize_t *)s2;

	if (*n1 != *n2)
	{
		if (*n1 > *n2)
			return (*n1 - *n2);
		else
			return (*n2 - *n1);
	}
	return (0);
}

size_t	ft_stcmp(const void *s1, const void *s2)
{
	const size_t	*n1 = (size_t *)s1;
	const size_t	*n2 = (size_t *)s2;

	if (*n1 != *n2)
	{
		if (*n1 > *n2)
			return (*n1 - *n2);
		else
			return (*n2 - *n1);
	}
	return (0);
}
