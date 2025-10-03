/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:34:35 by varias-c          #+#    #+#             */
/*   Updated: 2025/10/03 17:58:58 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*init_env(char **envp)
{
	t_list	*env_list;
	t_node	*env;
	int		i;

	env_list = ft_lstnew_list(sizeof(char));
	i = -1;
	while (envp[++i])
	{
		env = ft_lstnew_node(env_list->data_size * ft_strlen(envp[i]), envp[i]);
		ft_lstadd_back(env_list, env);
	}
	return (env_list);
}

static char	*getpath(t_list *env_list)
{
	t_node	*env;
	char	*value;

	env = env_list->head;
	while (env)
	{
		value = env->content;
		if (!ft_strncmp(value, "PATH=", 5))
			return (ft_substr(value, 5, ft_strlen(value) - 5));
		env = env->next;
	}
	return (NULL);
}

static char	*read_input(char *args)
{
	while (!args)
		args = readline("minishell > ");
	add_history(args);
	printf("%s\n", args);
	return (args);
}

static void	mini_loop(t_mini *minishell)
{
	char	*args;

	(void)minishell;
	args = NULL;
	while (1)
	{
		args = read_input(args);
		if (!args)
			continue ;
		args = expander(args);
		// TODO: Exec
		// minishell->exit_code = exec_input(minishell);
	}
	free(args);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	minishell;

	if (argc > 1 || argv[1])
	{
		printf("This program doesn't take arguments.\n");
		return (1);
	}
	// TODO: Signal handler (setup_signals)
	minishell.env = init_env(envp);
	minishell.cwd = getcwd(NULL, 0);
	minishell.path = getpath(minishell.env);
	mini_loop(&minishell);
	// TODO: Free all (PATH, cwd, envs, etc)
	return (0);
}
