/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrtab_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:26:23 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/18 14:24:27 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabmovebackall(ssize_t i, t_ptr_tab *tab)
{
	while (tab->start[i++])
	{
		tab->end[i - 1] = tab->start[i] + (tab->start[i] != NULL);
		tab->start[i] = tab->end[i] - (tab->end[i] != NULL);
	}
	tab->count -= !tab->start[tab->count - 1];
}

void	*ft_tabdelboth(ssize_t i, t_ptr_tab *tab)
{
	tab->start[i] = tab->end[i] - (tab->end[i] != NULL);
	ft_tabmovebackall(i, tab);
	tab->start[i] = tab->end[i] - (tab->end[i] != NULL);
	ft_tabmovebackall(i, tab);
	return (tab->start[i]);
}

void	*ft_tabdelone(t_bool start_or_end, ssize_t i, t_ptr_tab *tab)
{
	if (!start_or_end)
	{
		tab->start[i] = tab->end[i] - (tab->end[i] != NULL);
		ft_tabmovebackall(i, tab);
		return (tab->start[i]);
	}
	else
	{
		ft_tabmovebackall(i, tab);
		return (tab->end[i]);
	}
}
