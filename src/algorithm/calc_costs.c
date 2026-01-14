/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_costs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Cost Analysis
**
** Calculates the exact number of operations required to move each node to its
** target position. The cost includes:
**
** 1. Rotations needed to bring the node to the top of its stack
** 2. Rotations needed to bring the target to the top of the opposite stack
** 3. Optimizations when both can use simultaneous rotations (rr/rrr)
**
** Cost calculation considers:
** - Node position (index)
** - Whether above or below median (affects rotation direction)
** - Target position in opposite stack
** - Opportunity for combined rotations
**
** After calculating all costs, set_cheapest marks the node with the minimum
** cost, which will be chosen for the next move. This greedy approach ensures
** efficient overall performance.
*/

/*
** Returns the maximum of two integers.
**
** @param a: First integer
** @param b: Second integer
** @return: Larger of a and b
*/
static int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
** Calculates push_cost for each node in A when moving to B.
** Considers rotation costs and opportunities for combined rotations.
**
** @param a: Stack A (source)
** @param b: Stack B (destination)
*/
void	set_cost_a(t_stack *a, t_stack *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a)
	{
		a->push_cost = a->index;
		if (!a->above_median)
			a->push_cost = len_a - a->index;
		if (a->target_node && a->above_median
			&& a->target_node->above_median)
			a->push_cost = max_int(a->index, a->target_node->index);
		else if (a->target_node && !a->above_median
			&& !a->target_node->above_median)
			a->push_cost = max_int(len_a - a->index,
					len_b - a->target_node->index);
		else if (a->target_node && a->target_node->above_median)
			a->push_cost += a->target_node->index;
		else if (a->target_node)
			a->push_cost += len_b - a->target_node->index;
		a = a->next;
	}
}

/*
** Marks the node with the lowest push_cost as cheapest.
** Clears cheapest flag on all other nodes.
**
** @param stack: Stack to analyze
*/
void	set_cheapest(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*best;
	long	min_cost;

	tmp = stack;
	best = NULL;
	min_cost = LONG_MAX;
	while (tmp)
	{
		tmp->cheapest = false;
		if (tmp->push_cost < min_cost)
		{
			min_cost = tmp->push_cost;
			best = tmp;
		}
		tmp = tmp->next;
	}
	if (best)
		best->cheapest = true;
}
