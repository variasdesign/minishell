/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:45:40 by varias-c          #+#    #+#             */
/*   Updated: 2025/05/28 17:06:43 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstlast(t_list *list)
{
	t_node	*node;

	if (!list || !list->head || !list->tail)
		return (NULL);
	node = list->head;
	while (node->next)
		node = node->next;
	list->tail = node;
	return (list->tail);
}
