/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_finish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Inicializa dados auxiliares para mover de B -> A:
 * atualiza posições e define o target de cada nó de B em A.
 */
void	init_nodes_b(t_stack *a, t_stack *b)
{
	set_current_position(a);
	set_current_position(b);
	set_target_b(b, a);
}

/*
 * Move o topo de B para A, rotacionando A até o target ficar no topo.
 */
void	move_b_to_a(t_stack **a, t_stack **b)
{
	t_stack	*node;

	if (!a || !b || !*b)
		return ;
	node = *b;
	while (*a && node->target_node && *a != node->target_node)
	{
		set_current_position(*a);
		set_current_position(*b);
		if (node->target_node->above_median)
			ra(a, 1);
		else
			rra(a, 1);
	}
	pa(a, b, 1);
}
