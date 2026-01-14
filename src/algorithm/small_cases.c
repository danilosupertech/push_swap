/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Small Stack Sorting
**
** Optimized sorting for stacks with 2 or 3 elements. These cases are handled
** separately because they can be solved with a minimal, predetermined sequence
** of operations:
**
** - 2 elements: Simply swap if needed (1 operation max)
** - 3 elements: Uses at most 2 operations (combination of ra/rra/sa)
**
** The sort_three function finds the maximum element and positions it at the
** bottom, then performs a final swap if needed. This guarantees optimal
** operation count for these base cases.
*/

/*
** Sorts a stack with 2 or 3 elements using minimal operations.
** Returns immediately if already sorted or invalid stack.
**
** @param a: Pointer to stack A to sort
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
