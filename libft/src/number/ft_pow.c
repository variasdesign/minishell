/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:33:57 by varias-c          #+#    #+#             */
/*   Updated: 2025/06/23 22:37:52 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_pow_float(float base, float exp)
{
	float	num;

	num = 1;
	while (exp-- > 0)
		num = num * base;
	return (num);
}

int	ft_pow_int(int base, int exp)
{
	long	num;

	num = 1;
	while (exp-- > 0)
		num = num * base;
	return (num);
}
