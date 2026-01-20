/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:41:40 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/20 17:05:35 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_sorted(t_list *list)
{
	t_node	*current;
	t_env	*curr_var;
	t_env	*next_var;

	current = list->head;
	while (current->next)
	{
		curr_var = (t_env *)current->content;
		next_var = (t_env *)current->next->content;
		if (ft_strncmp(curr_var->key, next_var->key,
				ft_strlen(curr_var->key)) > 0)
			return (f);
		current = current->next;
	}
	return (t);
}

void	sort_exported_vars(t_list *sorted_env)
{
	t_node	*current;
	t_env	*curr_var;
	t_env	*next_var;

	if (!sorted_env || !sorted_env->head)
		return ;
	while (!is_sorted(sorted_env))
	{
		current = sorted_env->head;
		while (current->next)
		{
			curr_var = (t_env *)current->content;
			next_var = (t_env *)current->next->content;
			if (ft_strncmp(curr_var->key, next_var->key,
					ft_strlen(curr_var->key)) > 0)
				ft_lstswap_right(sorted_env, current);
			else
				current = current->next;
		}
	}
}
