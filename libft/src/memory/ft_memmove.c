/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:07:26 by varias-c          #+#    #+#             */
/*   Updated: 2024/10/01 18:40:30 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;
	size_t			i;

	if (!src && !dst)
		return (NULL);
	temp_dst = (unsigned char *) dst;
	temp_src = (unsigned char *) src;
	i = 0;
	if (dst > src)
		while (len-- > 0)
			temp_dst[len] = temp_src[len];
	else
	{
		while (i < len)
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}
