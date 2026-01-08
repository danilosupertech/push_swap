/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Retorna o nó marcado como cheapest na stack A.
 * static porque é um helper interno usado apenas neste ficheiro.
 */
static t_stack	*find_cheapest_node(t_stack *a)
{
	while (a)
	{
		if (a->cheapest)
			return (a);
		a = a->next;
	}
	return (NULL);
}

/*
** Faz rotações individuais quando rr/rrr não se aplicam.
** static porque só compõe a lógica do move_a_to_b() neste ficheiro.
*/
static void	do_single_rotations(t_stack **a, t_stack **b, t_stack *node)
{
	if (*a != node)
	{
		if (node->above_median)
			ra(a);
		else
			rra(a);
	}
	if (node->target_node && *b != node->target_node)
	{
		if (node->target_node->above_median)
			rb(b);
		else
			rrb(b);
	}
}

/*
 * Executa um passo de rotação para aproximar node e target do topo.
 * Usa rr/rrr quando ambos estão do mesmo lado da mediana.
 * static porque é um detalhe de implementação interno do algoritmo.
 */
static void	do_rotation_step(t_stack **a, t_stack **b, t_stack *node)
{
	if (node->target_node
		&& node->above_median
		&& node->target_node->above_median
		&& *a != node
		&& *b != node->target_node)
		rr(a, b);
	else if (node->target_node
		&& !node->above_median
		&& !node->target_node->above_median
		&& *a != node
		&& *b != node->target_node)
		rrr(a, b);
	else
		do_single_rotations(a, b, node);
}

/*
 * Roda A e B até node (em A) e o seu target (em B) ficarem no topo.
 * static porque é um helper usado apenas por move_a_to_b().
 */
static void	bring_nodes_to_top(t_stack **a, t_stack **b, t_stack *node)
{
	if (!node)
		return ;
	while ((*a) != node || (node->target_node && *b != node->target_node))
	{
		do_rotation_step(a, b, node);
	}
}

/*
 * Seleciona o nó cheapest em A, traz ele e o target em B para o topo
 * e faz pb.
 */
void	move_a_to_b(t_stack **a, t_stack **b)
{
	t_stack	*node;

	if (!a || !*a)
		return ;
	node = find_cheapest_node(*a);
	if (!node)
		return ;
	bring_nodes_to_top(a, b, node);
	pb(b, a);
}
