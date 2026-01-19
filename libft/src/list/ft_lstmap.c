/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:22:51 by varias-c          #+#    #+#             */
/*   Updated: 2025/05/28 18:22:16 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *list, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_node	*old_node;
	t_node	*new_node;
	void	*curr_content;

	new_list = NULL;
	if (!list || !f || !f)
		return (NULL);
	old_node = list->head;
	while (old_node)
	{
		curr_content = f(old_node->content);
		new_node = ft_lstnew_node(list->data_size, curr_content);
		if (!new_node)
		{
			del(curr_content);
			ft_lstdel_list(new_list, del);
			return (NULL);
		}
		ft_lstadd_back(new_list, new_node);
		old_node = old_node->next;
	}
	return (new_list);
}

/* int main () */
/* { */
/* 	t_list *lst; */
/* 	t_list *lstlen; */
/**/
/* 	lst = ft_lstnew(ft_strdup("hello!")); */
/* 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("how are you"))); */
/* 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("life is suffering"))); */
/* 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("oh look a cat"))); */
/* 	lstlen = ft_lstmap(lst, (void *)ft_strlen, free); */
/* 	ft_lstclear(&lst, free); */
/* } */
