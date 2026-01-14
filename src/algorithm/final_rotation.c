/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Final Rotation Phase
**
** After all elements are returned from B to A, the stack is sorted but the
** minimum value may not be at the top. This module performs the final
** adjustment to ensure the stack is properly oriented.
**
** It calculates the most efficient direction to rotate (ra vs rra) based on
** whether the minimum is in the first or second half of the stack. This
** ensures the stack meets the sorted requirement with minimal operations.
**
** Used as the last step in the Turk algorithm after all pushes are complete.
*/

/*
** Rotates stack A until the minimum value is at the top.
** Chooses the shorter rotation path (ra or rra).
**
** @param a: Pointer to stack A
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
