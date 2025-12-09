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

volatile sig_atomic_t	g_sig;

void	prompt_handler(int signum)
{
	g_sig = signum;
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal(SIGINT, prompt_handler);
	}
}

void	exec_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	input_signal(void)
{
	signal(SIGINT, prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}
