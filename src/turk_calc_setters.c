/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_calc_setters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Atualiza index/above_median para cada nó, com base no tamanho da stack.
 * above_median indica se o nó está na primeira metade (para escolher rotações).
 */
void	set_current_position(t_stack *stack)
{
	int	i;
	int	median;

	if (!stack)
		return ;
	i = 0;
	median = stack_len(stack) / 2;
	while (stack)
	{
		stack->index = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		i++;
	}
}

/*
 * Calcula push_cost para cada nó em A, considerando a posição do target em B.
 */
void	set_cost_a(t_stack *a, t_stack *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a)
	{
		a->push_cost = a->index;
		if (!a->above_median)
			a->push_cost = len_a - a->index;
		if (a->target_node && a->above_median
			&& a->target_node->above_median)
			a->push_cost = max_int(a->index, a->target_node->index);
		else if (a->target_node && !a->above_median
			&& !a->target_node->above_median)
			a->push_cost = max_int(len_a - a->index,
					len_b - a->target_node->index);
		else if (a->target_node && a->target_node->above_median)
			a->push_cost += a->target_node->index;
		else if (a->target_node)
			a->push_cost += len_b - a->target_node->index;
		a = a->next;
	}
}
