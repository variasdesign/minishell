/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:45:50 by varias-c          #+#    #+#             */
/*   Updated: 2025/07/27 14:02:43 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_offset(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			i = -i;
	return (i);
}

double	ft_atof(const char *str)
{
	t_bool	neg;
	double	result;
	double	divisor;
	int		i;

	i = get_offset(str);
	neg = i < 0;
	i = (-i * neg) + (i * !neg);
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	divisor = 0.1;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result + (str[i++] - '0') * divisor;
		divisor *= 0.1;
	}
	if (neg)
		return (-result);
	return (result);
}
