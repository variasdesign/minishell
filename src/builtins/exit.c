/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by jmellado          #+#    #+#             */
/*   Updated: 2025/12/30 12:41:02 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exit_atoi(char *str, long *result)
{
	int	sign;
	int	i;

	sign = 1;
	*result = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (f);
	while (str[i] && (ft_isdigit(str[i])))
	{
		*result = *result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] && !ft_isspace(str[i]))
		return (f);
	*result *= sign;
	return (t);
}

int	builtin_exit(char **args, t_bool *loop)
{
	long	exit_code;

	if (!exit_atoi(args[1], &exit_code))
	{
		ft_printf(2, E_SHELL_PERROR, "exit", "error converting number");
		return (255);
	}
	if (loop)
		*loop = f;
	if (!args[1])
		return(0);
	exit_code %= 256 + 256 * (exit_code < 0);
	return(exit_code);
}
