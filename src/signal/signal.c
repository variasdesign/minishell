/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:39:52 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/29 18:06:29 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://docs.rtems.org/releases/4.5.1-pre3/toolsdoc/gdb-5.0-docs/readline/readline00030.html

/* Handler que se reinstala automaticamente para prevenir exit del proceso */
void	auto_reinstall_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 130;
		write(STDOUT_FILENO, "\n", 1);
		
		/* Limpiar readline */
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		
		/* Reinstalar handler */
		signal(SIGINT, auto_reinstall_handler);
	}
}

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
	rl_catch_signals = 0;
	signal(SIGINT, auto_reinstall_handler);
	signal(SIGQUIT, SIG_IGN);
}