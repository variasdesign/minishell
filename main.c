/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:34:35 by varias-c          #+#    #+#             */
/*   Updated: 2025/09/15 17:23:57 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_mini *minishell, char **envp)
{
	minishell->env = envp;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	minishell;

	init_struct(&minishell, envp);
	show_prompt(&minishell);
	read_input(&minishell);
	parse_input(&minishell);
	exec_input(&minishell);
	signals(&minishell);
	save_history(&minishell);
}

void	random(t_mini *minishell)
{
	minishell->signals->sig;
}
