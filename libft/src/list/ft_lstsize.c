/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:41:20 by varias-c          #+#    #+#             */
/*   Updated: 2025/05/28 17:08:13 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstsize(t_list *list)
{
	t_node	*node;
	size_t	i;

	node = list->head;
	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	list->count = i;
	return (list->count);
}
