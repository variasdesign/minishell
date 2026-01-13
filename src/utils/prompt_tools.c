/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttonchak <ttonchak@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:07:49 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/12 18:28:38 by ttonchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_last_dir(t_list *env)
{
	char	*last_dir;
	t_env	*pwd;

	pwd = get_env(env, "PWD");
	if (pwd)
	{
		last_dir = ft_strrchr(pwd->value, '/');
		return (last_dir + (last_dir != ft_strlast(pwd->value)));
	}
	return ("");
}

static	char	*get_user(t_list *env)
{
	t_env	*user;

	user = get_env(env, "USER");
	if (user)
		return (user->value);
	return ("user");
}

// By using a combination of available environment variables,
// we assemble an informational prompt that displays the user
// and the current dir. If those envs are not available,
// we return placeholders.
// TODO: Read hostname by executing hostname or uname -n
// and redirecting its output to a string
char	*assemble_prompt(t_list *env, char *prompt)
{
	size_t	len;
	char	*prompt_parts[8];
	size_t	i;

	prompt_parts[0] = "[";
	prompt_parts[1] = get_user(env);
	prompt_parts[2] = "@";
	prompt_parts[3] = "hostname";
	prompt_parts[4] = " ";
	prompt_parts[5] = get_last_dir(env);
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
