/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:07:46 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/20 18:28:23 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstswap_between(t_list *list, t_node *prev, t_node *curr,
							t_node *next)
{
	if (curr != list->head)
	{
		prev->next = next;
		next->prev = prev;
	}
	else
	{
		next->prev = NULL;
		list->head = next;
	}
}

static void	ft_lstswap_behind(t_list *list, t_node *curr, t_node *prev,
							t_node *prev_of_prev)
{
	if (prev != list->head)
	{
		prev_of_prev->next = curr;
		curr->prev = prev_of_prev;
	}
	else
	{
		curr->prev = NULL;
		list->tail = curr;
	}
}

static void	ft_lstswap_ahead(t_list *list, t_node *curr, t_node *next,
							t_node *next_of_next)
{
	if (next != list->tail)
	{
		next_of_next->prev = curr;
		curr->next = next_of_next;
	}
	else
	{
		curr->next = NULL;
		list->tail = curr;
	}
}

void	ft_lstswap_left(t_list *list, t_node *curr)
{
	t_node	*next;
	t_node	*prev;
	t_node	*prev_of_prev;

	prev = curr->prev;
	next = curr->next;
	prev_of_prev = prev->prev;
	if (list->count > 1)
	{
		if (curr != list->head)
		{
			ft_lstswap_between(list, prev, curr, next);
			ft_lstswap_behind(list, curr, prev, prev_of_prev);
			prev->next = curr;
			curr->prev = prev;
		}
		else
			ft_lstswap_ends(list);
	}
}

void	ft_lstswap_right(t_list *list, t_node *curr)
{
	t_node	*prev;
	t_node	*next;
	t_node	*next_of_next;

	prev = curr->prev;
	next = curr->next;
	next_of_next = next->next;
	if (list->count > 1)
	{
		if (curr != list->tail)
		{
			ft_lstswap_between(list, prev, curr, next);
			ft_lstswap_ahead(list, curr, next, next_of_next);
			next->next = curr;
			curr->prev = next;
		}
		else
			ft_lstswap_ends(list);
	}
}
