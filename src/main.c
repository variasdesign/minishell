/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:34:35 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/10 13:11:25 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			g_sig;

static char	*read_input(char *args)
{
	while (!args)
		args = readline("minishell > ");
	add_history(args);
	return (args);
}

static void	mini_loop(t_mini *msh)
{
	char	*args;

	// t_cmd		cmd;
	args = NULL;
	while (1)
	{
		args = read_input(args);
		locate_quotes(args, msh->squote_tab, '\'');
		locate_quotes(args, msh->dquote_tab, '\"');
		validate_quotes(msh->squote_tab, msh->dquote_tab);
		locate_vars(args, msh->var_tab, *msh->squote_tab);
		args = expander(args, msh);
		// TODO: Lexer
		// args = lexer(args, msh);
		// TODO: Parser
		// args = parser(args, msh);
		// TODO: Exec
		// minishell->exit_code = exec_input(minishell);
		printf("%s\n", args);
		if (args)
			free(args);
		args = NULL;
		// TODO: Free allocated memory in pointer tables
	}
}

int	main(int argc, char *argv[])
{
	t_mini	*msh;

	if (argc > 1 || argv[1])
	{
		printf("This program doesn't take arguments.\n");
		return (1);
	}
	g_sig = 0;
	msh = allocate_minishell();
	if (!msh)
		return (EXIT_FAILURE);
	// TODO: Signal handler (setup_signals)
	msh->cwd = getcwd(NULL, 0);
	msh->path = getenv("PATH");
	signal(SIGINT, catch_int);
	signal(SIGTSTP, catch_suspend);
	mini_loop(msh);
	// TODO: Free all (PATH, cwd, envs, etc)
	return (0);
}
