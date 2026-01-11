/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_targets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Target Selection
**
** Determines the optimal insertion point for each element when moving between
** stacks. The target selection strategy maintains sort order:
**
** A → B (set_target_a):
**   Finds the largest value in B that is still smaller than the element.
**   If no such value exists, uses the maximum value in B.
**   This ensures elements are inserted in descending order in B.
**
** B → A (set_target_b):
**   Finds the smallest value in A that is larger than the element.
**   If no such value exists, uses the minimum value in A.
**   This maintains ascending order when returning elements to A.
**
** Correct target selection is crucial for minimizing total operations.
*/

/*
** Finds the best insertion point in B for a value from A.
** Returns the largest value smaller than val, or max if none exists.
**
** @param b: Stack B to search
** @param val: Value to find target for
** @return: Target node in B
*/
static t_stack	*find_target_in_b(t_stack *b, int val)
{
	t_stack	*best;
	t_stack	*it;

	if (!b)
		return (NULL);
	best = NULL;
	it = b;
	while (it)
	{
		if (it->value < val)
			if (!best || it->value > best->value)
				best = it;
		it = it->next;
	}
	if (best)
		return (best);
	return (find_max(b));
}

/*
** Sets target_node for each element in A, pointing to its insertion point in B.
**
** @param a: Stack A (source)
** @param b: Stack B (destination)
*/
void	set_target_a(t_stack *a, t_stack *b)
{
	t_stack	*tmp;

	tmp = a;
	while (tmp)
	{
		tmp->target_node = find_target_in_b(b, tmp->value);
		tmp = tmp->next;
	}
}

/*
** Finds the best insertion point in A for a value from B.
** Returns the smallest value larger than val, or min if none exists.
**
** @param a: Stack A to search
** @param val: Value to find target for
** @return: Target node in A
*/
static t_stack	*find_target_in_a(t_stack *a, int val)
{
	t_stack	*best;
	t_stack	*it;

	if (!a)
		return (NULL);
	best = NULL;
	it = a;
	while (it)
	{
		if (it->value > val)
		{
			if (!best || it->value < best->value)
				best = it;
		}
		it = it->next;
	}
	if (best)
		return (best);
	return (find_min(a));
}

/*
** Sets target_node for each element in B, pointing to its insertion point in A.
**
** @param b: Stack B (source)
** @param a: Stack A (destination)
*/
void	set_target_b(t_stack *b, t_stack *a)
{
	t_stack	*tmp;

	tmp = b;
	while (tmp)
	{
		tmp->target_node = find_target_in_a(a, tmp->value);
		tmp = tmp->next;
	}
}
