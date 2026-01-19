/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:35:17 by varias-c          #+#    #+#             */
/*   Updated: 2025/11/28 14:51:45 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_index(t_list *list, void (*del)(void *), ssize_t pos)
{
	if (pos > list->count)
		return ;
	ft_lstdel_wrapper(list, ft_lstfind_node(list, pos), del);
}

t_list	*ft_lstdel_list(t_list *list, void (*del)(void *))
{
	if (!list || !del)
		return (NULL);
	while (list->head)
		ft_lstdel_first(list, del);
	free(list);
	return (NULL);
}
