/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Libera todos os nós de uma stack e seta o ponteiro para NULL.
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
	*stack = NULL;
}

/*
 * Verifica se já existe um nó com o valor informado na stack.
 */
bool	check_duplicate(t_stack *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (true);
		stack = stack->next;
	}
	return (false);
}

/*
 * Adiciona um novo nó com valor `n` no fim da stack.
 */
void	append_node(t_stack **stack, int n)
{
	t_stack	*node;
	t_stack	*last;

	if (!stack)
		return ;
	node = (t_stack *)malloc(sizeof(t_stack));
	if (!node)
		return ;
	node->value = n;
	node->index = 0;
	node->push_cost = 0;
	node->above_median = false;
	node->cheapest = false;
	node->target_node = NULL;
	node->next = NULL;
	node->prev = NULL;
	if (!*stack)
	{
		*stack = node;
		return ;
	}
	last = find_last(*stack);
	last->next = node;
	node->prev = last;
}

/*
 * Retorna true se a stack estiver em ordem crescente.
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
