/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:20:43 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/20 19:37:27 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *list)
{
	t_list	*list_copy;
	t_node	*node;
	t_node	*node_copy;
	void	*content_copy;

	list_copy = ft_lstnew_list(list->data_size);
	node = list->head;
	while (node)
	{
		content_copy = malloc(list_copy->data_size);
		ft_memcpy(content_copy, node->content, list_copy->data_size);
		node_copy = ft_lstnew_node(list_copy->data_size, content_copy);
		ft_lstadd_back(list_copy, node_copy);
		node = node->next;
	}
	return (list_copy);
}
