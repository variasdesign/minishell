/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:05:56 by varias-c          #+#    #+#             */
/*   Updated: 2024/11/19 20:36:39 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_putnbr_signed(long nbr, char *base, int fd)
{
	int		base_length;
	size_t	count;

	count = 0;
	if (check_base(base) == 1)
		return (0);
	base_length = ft_strlen(base);
	if (base_length < 2)
		return (0);
	if (nbr < 0)
	{
		count += ft_putchar_fd('-', fd);
		nbr = nbr * -1;
	}
	if (nbr / base_length != 0)
		count += ft_putnbr_signed(nbr / base_length, base, fd);
	count += ft_putchar_fd(base[nbr % base_length], fd);
	return (count);
}

static int	ft_putnbr_unsigned(unsigned long nbr, char *base, int fd)
{
	int		base_length;
	size_t	count;

	count = 0;
	if (check_base(base) == 1)
		return (0);
	base_length = ft_strlen(base);
	if (base_length < 2)
		return (0);
	if (nbr / base_length != 0)
		count += ft_putnbr_unsigned(nbr / base_length, base, fd);
	count += ft_putchar_fd(base[nbr % base_length], fd);
	return (count);
}

size_t	ft_putnbr_fd(int n, int fd, char *base, t_bool sign)
{
	if (sign)
		return (ft_putnbr_signed(n, base, fd));
	else
		return (ft_putnbr_unsigned(n, base, fd));
}
/**/
/* int	main (int argc, char **argv) */
/* { */
/* 	if (argc != 2) */
/* 		return (1); */
/* 	ft_putnbr_fd(atoi(argv[1]), 2); */
/* 	return (0); */
/* } */
