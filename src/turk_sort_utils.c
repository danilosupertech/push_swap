/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 09:45:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Ordena uma stack com até 3 elementos usando apenas rotações e swap.
 * (Para 2 elementos, faz apenas sa.)
 */
void	sort_three(t_stack **a)
{
	int		len;
	t_stack	*max_node;

	if (!a || !*a || is_sorted(*a))
		return ;
	len = stack_len(*a);
	if (len == 2)
	{
		sa(a, 1);
		return ;
	}
	if (len != 3)
		return ;
	max_node = find_max(*a);
	if (max_node == *a)
		ra(a, 1);
	else if (max_node == (*a)->next)
		rra(a, 1);
	if ((*a)->value > (*a)->next->value)
		sa(a, 1);
}

/*
 * Faz rotações em A até o menor valor ficar no topo.
 */
void	min_on_top(t_stack **a)
{
	int		len;
	int		moves;
	t_stack	*min;

	if (!a || !*a)
		return ;
	set_current_position(*a);
	len = stack_len(*a);
	min = find_min(*a);
	if (!min)
		return ;
	moves = min->index;
	if (moves <= len / 2)
		while (moves--)
			ra(a, 1);
	else
	{
		moves = len - moves;
		while (moves--)
			rra(a, 1);
	}
}
