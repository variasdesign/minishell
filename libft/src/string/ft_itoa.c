/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:32:45 by varias-c          #+#    #+#             */
/*   Updated: 2024/11/14 19:35:31 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*putnbr(long n, int count, int pos, char *str)
{
	if (n < 0)
	{
		str[0] = '-';
		pos++;
		n = -n;
	}
	while (pos < count)
	{
		str[count - 2] = (n % 10) + 48;
		n = n / 10;
		count--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		magnitude;

	magnitude = nbrlen(n) + 1 + (n < 0);
	str = ft_calloc(magnitude, sizeof(char));
	if (!str)
		return (NULL);
	str = putnbr(n, magnitude, 1, str);
	str[magnitude - 1] = '\0';
	return (str);
}
/**/
/* int	main(int argc, char **argv) */
/* { */
/* 	if (argc != 2) */
/* 		return (1); */
/* 	int n = atoi(argv[1]); */
/* 	ft_itoa(n); */
/* } */
