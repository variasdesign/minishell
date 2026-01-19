/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:30:22 by varias-c          #+#    #+#             */
/*   Updated: 2024/09/24 19:47:15 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_intset(void *b, int c, size_t len)
{
	int	*temp;

	temp = (int *) b;
	while (len > 0)
	{
		*temp = c;
		temp++;
		len--;
	}
	return (b);
}
