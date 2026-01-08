/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_finish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Encontra o nó marcado como cheapest na stack (B).
 * static porque é um helper interno usado apenas neste ficheiro.
 */
static t_stack	*find_cheapest_node(t_stack *stack)
{
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

/*
 * Faz rotações individuais em B e A quando rr/rrr não se aplicam.
 * static porque implementa só um passo interno de move_b_to_a().
 */
static void	do_b_single_rotations(t_stack **a, t_stack **b, t_stack *node)
{
	if (*b != node)
	{
		if (node->above_median)
			rb(b);
		else
			rrb(b);
	}
	if (node->target_node && *a != node->target_node)
	{
		if (node->target_node->above_median)
			ra(a);
		else
			rra(a);
	}
}

/*
 * Executa um passo de rotação para aproximar node e target do topo.
 * Usa rr/rrr quando ambos estão do mesmo lado da mediana.
 * static porque é um detalhe do algoritmo, local a este ficheiro.
 */
static void	do_b_rotation_step(t_stack **a, t_stack **b, t_stack *node)
{
	if (node->target_node && node->above_median
		&& node->target_node->above_median
		&& *b != node && *a != node->target_node)
		rr(a, b);
	else if (node->target_node && !node->above_median
		&& !node->target_node->above_median
		&& *b != node && *a != node->target_node)
		rrr(a, b);
	else
		do_b_single_rotations(a, b, node);
}

/*
 * Roda B e A até node (em B) e o seu target (em A) ficarem no topo.
 * static porque só faz sentido como helper do move_b_to_a().
 */
static void	bring_b_nodes_to_top(t_stack **a, t_stack **b, t_stack *node)
{
	if (!node)
		return ;
	while ((*b) != node || (node->target_node && *a != node->target_node))
	{
		do_b_rotation_step(a, b, node);
	}
}

/*
** Seleciona o nó cheapest em B, traz ele e o target em A para o topo
** e faz pa. Move apenas um nó por chamada.
*/
void	move_b_to_a(t_stack **a, t_stack **b)
{
	t_stack	*node_to_move;

	if (!b || !*b)
		return ;
	node_to_move = find_cheapest_node(*b);
	if (!node_to_move)
		return ;
	bring_b_nodes_to_top(a, b, node_to_move);
	pa(a, b);
}
