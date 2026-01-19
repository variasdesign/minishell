/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:35:24 by varias-c          #+#    #+#             */
/*   Updated: 2024/10/07 18:49:17 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str = (unsigned char *) s;
	unsigned char		check;
	size_t				i;

	i = 0;
	check = (unsigned char) c;
	while (i < n && s)
	{
		if (str[i] == check)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
