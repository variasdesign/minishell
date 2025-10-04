/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:39:52 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/04 22:57:53 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_int(int sig_num)
{
	(void)sig_num;
	return ;
}
void	catch_suspend(int sig_num)
{
	(void)sig_num;
	return ;
}
