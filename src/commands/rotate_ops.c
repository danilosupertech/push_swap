/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Rotate Operations
**
** Implements ra, rb, and rr commands that rotate stacks upward.
** The first element becomes the last.
**
** - ra: rotate a - shift all elements up by 1 (first → last)
** - rb: rotate b - shift all elements up by 1 (first → last)  
** - rr: rotate both - ra and rb at the same time
**
** These operations are O(1) and essential for positioning elements.
*/

/*
** Rotates stack upward: first element becomes last.
** Does nothing if stack has fewer than 2 elements.
**
** @param stack: Pointer to the stack to rotate
*/
static void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = find_last(*stack);
	*stack = first->next;
	(*stack)->prev = NULL;
	first->next = NULL;
	first->prev = last;
	last->next = first;
}

/*
** Rotates stack a upward by 1.
**
** @param a: Pointer to stack a
** @param print: If 1, prints "ra" to stdout
*/
void	ra(t_stack **a, int print)
{
	rotate(a);
	if (print)
		ft_putstr_fd("ra\n", 1);
}

/*
** Rotates stack b upward by 1.
**
** @param b: Pointer to stack b
** @param print: If 1, prints "rb" to stdout
*/
void	rb(t_stack **b, int print)
{
	rotate(b);
	if (print)
		ft_putstr_fd("rb\n", 1);
}

/*
** Performs ra and rb simultaneously (rotates both stacks).
**
** @param a: Pointer to stack a
** @param b: Pointer to stack b
** @param print: If 1, prints "rr" to stdout
*/
void	rr(t_stack **a, t_stack **b, int print)
{
	rotate(a);
	rotate(b);
	if (print)
		ft_putstr_fd("rr\n", 1);
}
