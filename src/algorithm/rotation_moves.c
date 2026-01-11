/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 15:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Rotation Helper Functions
**
** Low-level rotation utilities used by move execution. These handle:
**
** - do_single_rotations: Individual ra/rra/rb/rrb when combined not possible
** - do_rotation_step: Single step with optimization for rr/rrr
** - bring_nodes_to_top: Loop to position nodes at stack tops
**
** These are static helpers only called from execute_moves.c via the
** public move_a_to_b and move_b_to_a functions.
*/

/*
** Performs individual rotations on stacks A and B.
** Used when combined rotations (rr/rrr) are not applicable.
**
** @param a: Pointer to stack A
** @param b: Pointer to stack B
** @param node: Node being moved with target information
*/
void	do_single_rotations(t_stack **a, t_stack **b, t_stack *node)
{
	if (*a != node)
	{
		if (node->above_median)
			ra(a, 1);
		else
			rra(a, 1);
	}
	if (node->target_node && *b != node->target_node)
	{
		if (node->target_node->above_median)
			rb(b, 1);
		else
			rrb(b, 1);
	}
}

/*
** Executes one rotation step, optimizing with rr/rrr when possible.
** Chooses combined rotation if both stacks rotate in same direction.
**
** @param a: Pointer to stack A
** @param b: Pointer to stack B
** @param node: Node being moved with target information
*/
void	do_rotation_step(t_stack **a, t_stack **b, t_stack *node)
{
	if (node->target_node
		&& node->above_median
		&& node->target_node->above_median
		&& *a != node
		&& *b != node->target_node)
		rr(a, b, 1);
	else if (node->target_node
		&& !node->above_median
		&& !node->target_node->above_median
		&& *a != node
		&& *b != node->target_node)
		rrr(a, b, 1);
	else
		do_single_rotations(a, b, node);
}

/*
** Rotates stacks until node is at top of A and target is at top of B.
** Updates positions dynamically during rotation.
**
** @param a: Pointer to stack A
** @param b: Pointer to stack B
** @param node: Node to bring to top with its target
*/
void	bring_nodes_to_top(t_stack **a, t_stack **b, t_stack *node)
{
	if (!node)
		return ;
	while ((*a) != node || (node->target_node && *b != node->target_node))
	{
		set_current_position(*a);
		set_current_position(*b);
		do_rotation_step(a, b, node);
	}
}
