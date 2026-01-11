/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Turk Algorithm Orchestration
**
** This file contains the main entry point and coordination logic for the
** Turk sorting algorithm. It manages the complete sorting flow:
**
** 1. Pushes initial elements from A to B (keeps at least 3 in A)
** 2. Iteratively pushes remaining elements using cost analysis
** 3. Sorts the final 3 elements in A using optimized rotations
** 4. Returns all elements from B to A in sorted order
** 5. Performs final rotation to place minimum at the top
**
** The algorithm minimizes operations by choosing the cheapest moves at each
** step, making it efficient for medium to large datasets.
*/

/*
** Pushes up to two elements from A to B if stack has more than 3 elements.
** This initializes stack B and ensures A has at least 3 elements for sort_three.
**
** @param a: Pointer to stack A
** @param b: Pointer to stack B
*/
static void	push_two_to_b(t_stack **a, t_stack **b)
{
	if (stack_len(*a) > 3)
		pb(a, b, 1);
	if (stack_len(*a) > 3)
		pb(a, b, 1);
}

/*
** Continues pushing elements from A to B until only 3 remain in A.
** Uses cost analysis to select the cheapest element to push at each iteration.
**
** @param a: Pointer to stack A
** @param b: Pointer to stack B
*/
static void	push_a_to_b_until_three(t_stack **a, t_stack **b)
{
	while (stack_len(*a) > 3)
	{
		init_nodes_a(*a, *b);
		move_a_to_b(a, b);
	}
}

/*
** Moves all elements from B back to A in the correct sorted positions.
** Each element is placed at its target position to maintain sort order.
**
** @param a: Pointer to stack A
** @param b: Pointer to stack B
*/
static void	push_b_to_a_all(t_stack **a, t_stack **b)
{
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
}

/*
** Main entry point for the Turk sorting algorithm.
** Coordinates all phases: initial pushes, iterative sorting, final cleanup.
**
** @param a: Pointer to stack A (contains all elements initially)
** @param b: Pointer to stack B (empty initially)
*/
void	turk_sort(t_stack **a, t_stack **b)
{
	push_two_to_b(a, b);
	push_a_to_b_until_three(a, b);
	sort_three(a);
	push_b_to_a_all(a, b);
	set_current_position(*a);
	min_on_top(a);
}
