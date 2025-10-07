/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:34:35 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/04 22:48:35 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	g_sig;

static char	*read_input(char *args)
{
	while (!args)
		args = readline("minishell > ");
	add_history(args);
	printf("%s\n", args);
	return (args);
}

static t_expander	*allocate_expander(void)
{
	t_expander	*ex;

	ex = ft_calloc(1, sizeof(t_expander));
	if (!ex)
		return (NULL);
	ex->squote_tab = ft_calloc(1, sizeof(t_ptr_tab));
	if (!ex->squote_tab)
	{
		free (ex);
		return (NULL);
	}
	ex->var_tab = ft_calloc(1, sizeof(t_ptr_tab));
	if (!ex->var_tab)
	{
		free (ex);
		free (ex->squote_tab);
		return (NULL);
	}
	return (ex);
}

static void	mini_loop(t_mini *minishell)
{
	t_expander	*ex;
	// t_lexer		lex;
	// t_cmd		cmd;
	char		*args;

	(void)minishell;
	args = NULL;
	ex = allocate_expander();
	while (1)
	{
		args = read_input(args);
		args = expander(args, ex);
		// TODO: Lexer
		// args = lexer(ex.var_tab->orig, &lex);
		// TODO: Parser
		// args = lexer(ex.var_tab->orig, &lex);
		// TODO: Exec
		// minishell->exit_code = exec_input(minishell);
		if (args)
			free(args);
		args = NULL;
	}
}

int	main(int argc, char *argv[])
{
	t_mini	minishell;

	g_sig = 0;
	if (argc > 1 || argv[1])
	{
		printf("This program doesn't take arguments.\n");
		return (1);
	}
	// TODO: Signal handler (setup_signals)
	minishell.cwd = getcwd(NULL, 0);
	minishell.path = getenv("PATH");
	signal(SIGINT, catch_int);
	signal(SIGTSTP, catch_suspend);
	mini_loop(&minishell);
	// TODO: Free all (PATH, cwd, envs, etc)
	return (0);
}
