/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:09:18 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 18:39:51 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_newline_flag(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		if (args[i][j] == '\0')
			break ;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0' && j > 1)
			i++;
		else
			break ;
	}
	return (i * (i > 1));
}

static void	print_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		ft_printf(1, "%s", args[i]);
		if (args[i + 1])
			ft_printf(1, " ");
		i++;
	}
}

int	builtin_echo(char **args)
{
	int	newline;
	int	flag_count;

	newline = 1;
	flag_count = has_newline_flag(args);
	if (flag_count)
	{
		newline = 0;
		print_args(args, flag_count);
	}
	else
		print_args(args, 1);
	if (newline)
		ft_printf(1, "\n");
	return (0);
}
