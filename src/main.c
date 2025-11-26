/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:34:35 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/21 15:23:52 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

static char	*get_last_dir(void)
{
	char	*last_dir;
	char	*pwd;

	pwd = getenv("PWD");
	last_dir = ft_strrchr(pwd, '/');
	return (last_dir + (last_dir != ft_strlast(pwd)));
}

// TODO: Read hostname by executing hostname or uname -n
// and redirecting its output to a string
static char	*assemble_prompt(char **env_list, char *prompt)
{
	size_t	len;
	char	*prompt_parts[8];
	size_t	i;

	prompt_parts[0] = "[";
	prompt_parts[1] = get_env(env_list, "USER");
	prompt_parts[2] = "@";
	prompt_parts[3] = "hostname";
	prompt_parts[4] = " ";
	prompt_parts[5] = get_last_dir();
	prompt_parts[6] = "]$ ";
	prompt_parts[7] = 0;
	len = 0;
	i = 0;
	while (prompt_parts[i])
		len += ft_strlen(prompt_parts[i++]);
	prompt = ft_calloc(len + 1, sizeof(char));
	if (!prompt)
		return (NULL);
	i = 0;
	while (prompt_parts[i])
		ft_strlcat(prompt, prompt_parts[i++], len + 1);
	return (prompt);
}

// TODO: Read on rl_done global var
static char	*read_input(char *args, char **env_list, char *prompt)
{
	extern int	rl_done;

	if (args)
	{
		free(args);
		args = NULL;
	}
	while (!args)
	{
		if (prompt)
		{
			free(prompt);
			prompt = NULL;
		}
		prompt = assemble_prompt(env_list, prompt);
		args = readline(prompt);
	}
	if (args && *args)
		add_history(args);
	return (args);
}

static void	mini_loop(t_mini *msh)
{
	char	*args;
	char	*prompt;
	t_list	*token_list;

	args = NULL;
	prompt = NULL;
	while (1)
	{
		args = read_input(args, msh->env, prompt);
		args = expander(args, msh->squote_tab, msh->dquote_tab, msh->var_tab);
		token_list = lexer(args, msh);
		msh->cmd_list = parser(token_list);
		if (!msh->cmd_list)
			continue ;
		msh->exit_code = exec_input(msh->cmd_list, msh->env);
	}
}

// TODO: Norminette E V E R Y T H I N G
int	main(int argc, char *argv[], char *envp[])
{
	t_mini	*msh;

	if (argc > 1 || argv[1])
	{
		printf("This program doesn't take arguments.\n");
		return (1);
	}
	g_sig = 0;
	msh = allocate_minishell(envp);
	if (!msh)
		return (EXIT_FAILURE);
	// TODO: Signal handler (setup_signals)
	msh->cwd = getcwd(NULL, 0);
	msh->path = get_env(msh->env, "PATH");
	signal(SIGINT, catch_int);
	signal(SIGTSTP, catch_suspend);
	mini_loop(msh);
	// TODO: Free allocated memory in pointer tables
	// TODO: Free all (PATH, cwd, envs, etc)
	return (0);
}
