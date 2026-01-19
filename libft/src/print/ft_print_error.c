/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:15:48 by varias-c          #+#    #+#             */
/*   Updated: 2025/07/26 17:21:34 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_perror(char *msg, char *err, t_bool must_exit, int exit_code)
{
	if (!msg)
		ft_printf(2, "%s\n", err);
	else if (!err)
		ft_printf(2, msg);
	else
		ft_printf(2, msg, err);
	if (must_exit)
		exit(exit_code);
}
