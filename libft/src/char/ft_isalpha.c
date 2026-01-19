/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:02:29 by varias-c          #+#    #+#             */
/*   Updated: 2024/09/23 20:02:32 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	return (!(c < 65 || c > 90));
}

static int	ft_islower(int c)
{
	return (!(c < 97 || c > 122));
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
