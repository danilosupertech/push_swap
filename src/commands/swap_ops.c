/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Swap Operations
**
** Implements the sa, sb, and ss commands that swap the first two elements
** of a stack. This is one of the fundamental operations in the push_swap
** algorithm.
**
** - sa: swap a - swap the first 2 elements of stack a
** - sb: swap b - swap the first 2 elements of stack b  
** - ss: swap both - sa and sb at the same time
**
** These operations are O(1) and crucial for small adjustments during sorting.
*/

/*
** Swaps the top two elements of a stack.
** Does nothing if stack has fewer than 2 elements.
**
** @param stack: Pointer to the stack to swap
*/

static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	first->prev = second;
	second->next = first;
	*stack = second;
}

/*
** Swaps the first two elements of stack a.
**
** @param a: Pointer to stack a
** @param print: If 1, prints "sa" to stdout
*/
void	sa(t_stack **a, int print)
{
	swap(a);
	if (print)
		ft_putstr_fd("sa\n", 1);
}

/*
** Swaps the first two elements of stack b.
**
** @param b: Pointer to stack b
** @param print: If 1, prints "sb" to stdout
*/
void	sb(t_stack **b, int print)
{
	swap(b);
	if (print)
		ft_putstr_fd("sb\n", 1);
}

/*
** Performs sa and sb simultaneously (swaps both stacks).
**
** @param a: Pointer to stack a
** @param b: Pointer to stack b
** @param print: If 1, prints "ss" to stdout
*/
void	ss(t_stack **a, t_stack **b, int print)
{
	swap(a);
	swap(b);
	if (print)
		ft_putstr_fd("ss\n", 1);
}
