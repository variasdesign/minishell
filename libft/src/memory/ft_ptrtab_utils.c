/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrtab_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varias-c <varias-c@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:14:14 by varias-c          #+#    #+#             */
/*   Updated: 2025/12/18 14:16:34 by varias-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Check if ptr is inside start and end of any pointer range in table
// TODO: Binary search to optimize times
ssize_t	ft_tabfind(void *ptr, t_ptr_tab tab, t_bool inclusive)
{
	ssize_t	i;

	i = 0;
	while (i < tab.count && tab.start[i] && tab.end[i])
	{
		if ((inclusive && ptr >= tab.start[i] && ptr < tab.end[i])
			|| (ptr > tab.start[i] && ptr < tab.end[i]))
			return (i);
		i++;
	}
	return (-1);
}

// tab1 and tab2 exists and tab1 has pointers
// but tab2 doesn't have pointers = true
// tab2 and tab1 exists and tab2 has pointers
// but tab1 doesn't have pointers = false
// tab1 exists and has pointers and tab2 exists
// and has pointers, but t1i is before t2i = true
// tab1 exists and has pointers and tab2 exists
// and has pointers, but t2i is before t1i = false
// tab1 exists and doesn't have pointers
// and tab2 doesn't have pointers = undefined
t_bool	ft_tabcmp(t_ptr_tab *tab1, t_ptr_tab *tab2, size_t t1i, size_t t2i)
{
	if ((tab1 && tab2) && (tab1->start) && (tab1->start[t1i])
		&& (!tab2->start || !tab2->start[t2i]
			|| tab1->start[t1i] < tab2->start[t2i]))
		return (t);
	return (f);
}

ssize_t	ft_tabptrlen(ssize_t i, t_ptr_tab tab)
{
	if (tab.start[i] && tab.end[i])
		return (tab.end[i] - tab.start[i]);
	return (-1);
}
