/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:01:32 by varias-c          #+#    #+#             */
/*   Updated: 2025/05/28 18:10:55 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// FIX: Return something to indicate error in all these functions
void	ft_lstadd_front(t_list *list, t_node *new_node)
{
	if (!list || !new_node)
		return ;
	if (!list->head)
	{
		list->tail = new_node;
		list->head = new_node;
		new_node->next = NULL;
	}
	else
	{
		new_node->next = list->head;
		new_node->next->prev = new_node;
		list->head = new_node;
	}
	new_node->prev = NULL;
	list->count++;
}

void	ft_lstadd_back(t_list *list, t_node *new_node)
{
	if (!list || !new_node)
		return ;
	if (!list->head)
	{
		list->head = new_node;
		list->tail = new_node;
		new_node->prev = NULL;
	}
	else
	{
		list->tail->next = new_node;
		new_node->prev = list->tail;
		list->tail = new_node;
	}
	new_node->next = NULL;
	list->count++;
}

void	ft_lstadd_insert(t_list *list, t_node *new_node, t_node *node)
{
	if (!list || !new_node || !node)
		return ;
	if (!list->head)
		ft_lstadd_front(list, new_node);
	else if (node == list->tail)
		ft_lstadd_back(list, new_node);
	else
	{
		new_node->next = node->next;
		new_node->prev = node;
		new_node->next->prev = new_node;
		node->next = new_node;
	}
	list->count++;
}

void	ft_lstadd_insert_pos(t_list *list, t_node *new_node, ssize_t pos)
{
	t_node	*node;

	if (!list || !new_node || pos < 0 || pos >= list->count)
		return ;
	if (!list->head)
		ft_lstadd_front(list, new_node);
	else if (pos + 1 == list->count)
		ft_lstadd_back(list, new_node);
	else
	{
		node = ft_lstfind_node(list, pos);
		new_node->next = node->next;
		new_node->prev = node;
		new_node->next->prev = new_node;
		node->next = new_node;
	}
	list->count++;
}
