/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:07:49 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/10 18:07:59 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_last_dir(t_list *env)
{
	char	*last_dir;
	char	*pwd;

	pwd = get_env(env, "PWD")->value;
	last_dir = ft_strrchr(pwd, '/');
	return (last_dir + (last_dir != ft_strlast(pwd)));
}

// TODO: Read hostname by executing hostname or uname -n
// and redirecting its output to a string
char	*assemble_prompt(t_list *env, char *prompt)
{
	size_t	len;
	char	*prompt_parts[8];
	size_t	i;

	prompt_parts[0] = "[";
	prompt_parts[1] = get_env(env, "USER")->value;
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
