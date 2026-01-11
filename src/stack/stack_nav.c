/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_nav.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Stack Navigation
**
** Provides basic navigation and measurement functions for stack structures.
** These are fundamental utilities used throughout the algorithm:
**
** - stack_len: Returns the number of elements in a stack
** - find_last: Locates the last node in a stack
**
** Both operations traverse the linked list and are O(n) in complexity.
** Used extensively for indexing, positioning, and size calculations.
*/

/*
** Counts and returns the number of elements in the stack.
**
** @param stack: Stack to measure
** @return: Number of nodes in the stack
*/
int	stack_len(t_stack *stack)
{
	int		i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

/*
** Finds and returns the last node in the stack.
**
** @param stack: Stack to search
** @return: Pointer to last node, or NULL if stack is empty
*/
t_stack	*find_last(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}
