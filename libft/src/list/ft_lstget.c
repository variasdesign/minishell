/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:11:13 by varias-c          #+#    #+#             */
/*   Updated: 2025/05/28 19:15:26 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstget_data_index(t_list *list, ssize_t index)
{
	t_node	*node;

	node = ft_lstfind_node(list, index);
	if (node)
		return (node->content);
	return (NULL);
}

void	*ft_lstget_data_node(t_node *node)
{
	if (node)
		return (node->content);
	return (NULL);
}
