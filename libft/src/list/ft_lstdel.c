/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:13:13 by varias-c          #+#    #+#             */
/*   Updated: 2025/06/17 19:21:18 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdel_node(t_node *node, void (*del)(void *))
{
	if (!node || !del)
		return ;
	del(node->content);
	free(node);
}

void	ft_lstdel_wrapper(t_list *list, t_node *node, void (*del)(void *))
{
	if (node == list->head)
		ft_lstdel_first(list, del);
	else if (node == list->tail)
		ft_lstdel_last(list, del);
	else
		ft_lstdel_between(list, node, del);
}

void	ft_lstdel_between(t_list *list, t_node *node, void (*del)(void *))
{
	t_node	*tmp;

	tmp = node;
	if (node)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		ft_lstdel_node(node, del);
		list->count--;
	}
}

void	ft_lstdel_first(t_list *list, void (*del)(void *))
{
	t_node	*tmp;

	if (list->head)
	{
		tmp = list->head->next;
		ft_lstdel_node(list->head, del);
		list->head = tmp;
		if (list->head)
			list->head->prev = NULL;
		list->count--;
	}
}

void	ft_lstdel_last(t_list *list, void (*del)(void *))
{
	t_node	*tmp;

	if (list->tail)
	{
		tmp = list->tail->prev;
		ft_lstdel_node(list->tail, del);
		list->tail = tmp;
		if (list->tail)
			list->tail->next = NULL;
		list->count--;
	}
}
