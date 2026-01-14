/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Stack Order Analysis
**
** Provides functions to analyze ordering and find extremes in stacks.
** These utilities are essential for:
**
** - is_sorted: Check if stack is in ascending order (early exit optimization)
** - find_min: Locate the node with minimum value
** - find_max: Locate the node with maximum value
**
** Used extensively in sorting logic, target selection, and final positioning.
** All operations are O(n) as they traverse the entire stack.
*/

/*
** Checks if the stack is sorted in ascending order.
**
** @param stack: Stack to check
** @return: true if sorted, false otherwise (empty stack returns true)
*/
bool	is_sorted(t_stack *stack)
{
	if (!stack)
		return (true);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

/*
** Finds and returns the node with the minimum value.
**
** @param stack: Stack to search
** @return: Pointer to node with minimum value, or NULL if empty
*/
t_stack	*find_min(t_stack *stack)
{
	t_stack	*min;

	if (!stack)
		return (NULL);
	min = stack;
	while (stack)
	{
		if (stack->value < min->value)
			min = stack;
		stack = stack->next;
	}
	return (min);
}

/*
** Finds and returns the node with the maximum value.
**
** @param stack: Stack to search
** @return: Pointer to node with maximum value, or NULL if empty
*/
t_stack	*find_max(t_stack *stack)
{
	t_stack	*max;

	if (!stack)
		return (NULL);
	max = stack;
	while (stack)
	{
		if (stack->value > max->value)
			max = stack;
		stack = stack->next;
	}
	return (max);
}
