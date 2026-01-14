/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Push Operations
**
** Implements the pa and pb commands that move elements between stacks.
** These are critical operations in the push_swap algorithm.
**
** - pa: push a - take the first element from b and put it on top of a
** - pb: push b - take the first element from a and put it on top of b
**
** These operations run in constant time O(1) by only manipulating the top
** node pointers, regardless of stack size. They form the core of all moves.
*/

/*
** Moves the top element from src stack to dst stack.
** Does nothing if src is empty.
**
** @param dst: Destination stack
** @param src: Source stack
*/
static void	push(t_stack **dst, t_stack **src)
{
	t_stack	*node_to_push;

	if (!src || !*src)
		return ;
	node_to_push = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node_to_push->prev = NULL;
	if (!*dst)
	{
		*dst = node_to_push;
		node_to_push->next = NULL;
	}
	else
	{
		node_to_push->next = *dst;
		(*dst)->prev = node_to_push;
		*dst = node_to_push;
	}
}

/*
** Pushes the top element from b to a.
**
** @param a: Pointer to stack a (destination)
** @param b: Pointer to stack b (source)
** @param print: If 1, prints "pa" to stdout
*/
void	pa(t_stack **a, t_stack **b, int print)
{
	push(a, b);
	if (print)
		ft_putstr_fd("pa\n", 1);
}

/*
** Pushes the top element from a to b.
**
** @param a: Pointer to stack a (source)
** @param b: Pointer to stack b (destination)
** @param print: If 1, prints "pb" to stdout
*/
void	pb(t_stack **a, t_stack **b, int print)
{
	push(b, a);
	if (print)
		ft_putstr_fd("pb\n", 1);
}
