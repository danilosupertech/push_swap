/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Stack Memory Management
**
** Handles stack node allocation, initialization, and cleanup.
** Core functions:
**
** - append_node: Creates and adds a new node to the end of a stack
** - free_stack: Deallocates all nodes and resets the stack pointer
**
** These operations manage the lifecycle of stack nodes, ensuring proper
** memory allocation and preventing leaks. Critical for program reliability.
*/

/*
** Creates a new node with value n and appends it to the end of the stack.
** Initializes all node fields to default values.
**
** @param stack: Pointer to stack pointer
** @param n: Integer value to store in the new node
*/
void	append_node(t_stack **stack, int n)
{
	t_stack	*new;
	t_stack	*last;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return ;
	new->value = n;
	new->index = 0;
	new->push_cost = 0;
	new->above_median = false;
	new->cheapest = false;
	new->target_node = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = find_last(*stack);
	last->next = new;
	new->prev = last;
}

/*
** Frees all nodes in the stack and sets the stack pointer to NULL.
** Prevents memory leaks by deallocating every node.
**
** @param stack: Pointer to stack pointer to free
*/
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}
