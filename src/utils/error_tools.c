/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:38:08 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/24 18:38:15 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *msg, char *err, int exit_code)
{
	print_error(msg, err);
	exit(exit_code);
}

void	print_error(char *msg, char *err)
{
	if (!err && !msg)
		perror(NULL);
	else if (!msg)
		ft_printf(2, "%s\n", err);
	else if (!err)
		ft_printf(2, msg);
	else
		ft_printf(2, msg, err);
}
