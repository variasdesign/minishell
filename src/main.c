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
		ft_lstadd_front(env_list, env);
	}
	return (env_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	minishell;
	char	*args;

	(void)argc;
	(void)argv;
	minishell.env = init_env(envp);
	args = readline("minishell > ");
	ft_printf(1, "%s\n", args);
	// read_input(&minishell);
	// parse_input(&minishell);
	// exec_input(&minishell);
	// signals(&minishell);
	// save_history(&minishell);
}
