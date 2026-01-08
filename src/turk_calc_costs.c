/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_calc_costs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Calcula push_cost para um nó em B, considerando a posição do target em A.
 * static porque é um helper usado apenas por set_cost_b() neste ficheiro.
 */
static void	calc_b_cost(t_stack *b, int len_a, int len_b)
{
	b->push_cost = b->index;
	if (!b->above_median)
		b->push_cost = len_b - b->index;
	if (b->target_node && b->above_median
		&& b->target_node->above_median)
		b->push_cost = max_int(b->index, b->target_node->index);
	else if (b->target_node && !b->above_median
		&& !b->target_node->above_median)
		b->push_cost = max_int(len_b - b->index,
				len_a - b->target_node->index);
	else if (b->target_node && b->target_node->above_median)
		b->push_cost += b->target_node->index;
	else if (b->target_node)
		b->push_cost += len_a - b->target_node->index;
}

/*
 * Calcula push_cost para cada nó de B, considerando a posição do target em A.
 */
void	set_cost_b(t_stack *b, t_stack *a)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (b)
	{
		calc_b_cost(b, len_a, len_b);
		b = b->next;
	}
}

/*
 * Marca como cheapest o nó com menor push_cost (limpa flags anteriores).
 */
void	set_cheapest(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*best;
	long	min_cost;

	tmp = stack;
	best = NULL;
	min_cost = LONG_MAX;
	while (tmp)
	{
		tmp->cheapest = false;
		if (tmp->push_cost < min_cost)
		{
			min_cost = tmp->push_cost;
			best = tmp;
		}
		tmp = tmp->next;
	}
	if (best)
		best->cheapest = true;
}
