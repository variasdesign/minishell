/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:10:45 by varias-c          #+#    #+#             */
/*   Updated: 2026/01/20 18:10:52 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap_ends(t_list *list)
{
	t_node	*tmp;

	if (list->count > 1)
	{
		list->tail->next = list->head->next;
		list->head->next = NULL;
		list->head->prev = list->tail->prev;
		list->tail->prev = NULL;
		tmp = list->head;
		list->head = list->tail;
		list->tail = tmp;
	}
}
