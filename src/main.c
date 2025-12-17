/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:34:35 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/15 19:51:23 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_input(char **args, t_list *env, char **prompt)
{
	char	*tmp;

	if (*args)
		free(*args);
	if (*prompt)
		free(*prompt);
	*args = NULL;
	*prompt = NULL;
	*prompt = assemble_prompt(env, *prompt);
	input_signal();
	if (isatty(STDIN_FILENO))
		*args = readline(*prompt);
	else
		*args = get_next_line(STDIN_FILENO);
	tmp = ft_strtrim(*args, "\t\n\v\f\r ");
	free(*args);
	*args = tmp;
	if (args && *args && !ft_isspace(**args))
		add_history(*args);
	return (*args);
}

static int	mini_loop(t_mini *msh)
{
	while (msh->loop)
	{
		msh->input = read_input(&msh->input, msh->env, &msh->prompt);
		msh->loop = msh->input != NULL;
		if (msh->input && *msh->input)
		{
			msh->input = expander(msh);
			if (!msh->input)
				continue ;
			msh->token_list = lexer(msh);
			if (!msh->token_list)
				continue ;
			msh->cmd_list = parser(msh->token_list);
			free_tables(msh, f);
			if (!msh->cmd_list)
				continue ;
			if (exec_cmd_list(msh, msh->cmd_list, msh->env) < 0)
				ft_perror(E_EXEC_FAILURE, NULL, f, 0);
			msh->cmd_list = ft_lstdel_list(msh->cmd_list, free_cmd_list);
			msh->cmd_since_last_pipe = f;
		}
	}
	return (g_sig);
}

// TODO: Norminette E V E R Y T H I N G
int	main(int argc, char *argv[], char *envp[])
{
	t_mini	*msh;

	if (argc > 1 || argv[1])
	{
		printf(E_ARGS_NOT_TAKEN);
		return (1);
	}
	g_sig = 0;
	msh = allocate_minishell(envp);
	if (!msh)
		return (EXIT_FAILURE);
	mini_loop(msh);
	free_all(msh);
	// write(STDOUT_FILENO, "exit\n", 5);
	return (g_sig);
}
