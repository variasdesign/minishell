/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:43:18 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/04 13:08:32 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *orig)
{
	const size_t	len = ft_strlen(orig);
	char			*dup;

	dup = ft_calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	dup = ft_memcpy(dup, orig, len);
	return (dup);
}
