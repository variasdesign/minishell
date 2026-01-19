/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:35:39 by varias-c          #+#    #+#             */
/*   Updated: 2025/04/12 19:00:54 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	check_specifiers(const char *s)
{
	if (!s)
		return (f);
	while (*s)
	{
		if (*s == '%')
		{
			if (!(char *)ft_memchr((void *) VAR_SPECIFIERS,
					*s, ft_strlen(VAR_SPECIFIERS)))
				return (f);
		}
		s++;
	}
	return (t);
}
