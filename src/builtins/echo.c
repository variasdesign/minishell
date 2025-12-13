/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:09:18 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/13 16:24:21 by jmellado         ###   ########.fr       */
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
			break;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0' && j > 1)
			i++;
		else
			break;
	}
	return (i > 1 ? i : 0);
}

static void	print_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int	builtin_echo(char **args, char ***env)
{
	int	newline;
	int	flag_count;

	(void)env;
	newline = 1;
	flag_count = has_newline_flag(args);
	if (flag_count > 0)
	{
		newline = 0;
		print_args(args, flag_count);
	}
	else
		print_args(args, 1);
	if (newline)
		printf("\n");
	return (0);
}