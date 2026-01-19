/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:23:20 by varias-c          #+#    #+#             */
/*   Updated: 2025/05/28 18:16:35 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstnew_node(ssize_t data_size, void *content)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	if (!node)
		return (NULL);
	node->content = malloc(data_size);
	if (!node->content)
	{
		free (node);
		return (NULL);
	}
	ft_memcpy(node->content, content, data_size);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstnew_list(ssize_t data_size)
{
	t_list	*list;

	if (!(data_size > 0))
		return (NULL);
	list = malloc(sizeof(t_list));
	list->count = 0;
	list->data_size = data_size;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}
