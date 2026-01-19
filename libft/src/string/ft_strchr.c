/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:14:20 by varias-c          #+#    #+#             */
/*   Updated: 2024/10/03 18:21:59 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t n)
{
	return ((char *)ft_memchr((void *) s, c, n));
}

char	*ft_strchr(const char *s, int c)
{
	return ((char *)ft_memchr((void *) s, c, ft_strlen(s) + 1));
}
