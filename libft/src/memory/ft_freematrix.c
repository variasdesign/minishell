/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:15:50 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:45:17 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_freematrix(void **matrix)
{
	const size_t	count = ft_arrlen(matrix);
	size_t			i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (i < count)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}
