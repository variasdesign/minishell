/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:39:52 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/29 13:59:54 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = 130;
		printf("^C\n");
	}
}

void	quit(int signal)
{
	if (signal == SIGQUIT)
	{
		g_sig = 131;
		printf("minishell: quit process\n");
	}
}

void	redisplay(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exec_signal(void)
{
	signal(SIGINT, interrupt);
	signal(SIGQUIT, quit);
}

void	input_signal(void)
{
	signal(SIGINT, redisplay);
	signal(SIGQUIT, SIG_IGN);
}