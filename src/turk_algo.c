/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 09:45:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Empurra até dois elementos de A para B, se A tiver mais de 3.
 * static porque é um detalhe interno do fluxo do turk e não deve
 * ser exposto fora deste ficheiro.
 */
static void	push_two_to_b(t_stack **a, t_stack **b)
{
	if (stack_len(*a) > 3)
		pb(a, b, 1);
	if (stack_len(*a) > 3)
		pb(a, b, 1);
}

/*
 * Continua a empurrar de A para B até restarem 3 elementos em A.
 * static porque só é usado por turk_sort() neste ficheiro.
 */
static void	push_a_to_b_until_three(t_stack **a, t_stack **b)
{
	while (stack_len(*a) > 3)
	{
		init_nodes_a(*a, *b);
		move_a_to_b(a, b);
	}
}

/*
 * Move todos os elementos de B de volta para A, um a um.
 * static porque é um passo interno do turk e não faz parte da API.
 */
static void	push_b_to_a_all(t_stack **a, t_stack **b)
{
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
}

/*
 * Inicializa campos auxiliares dos nós em A: posição atual, target em B,
 * custo de push e flag cheapest.
 */
void	init_nodes_a(t_stack *a, t_stack *b)
{
	set_current_position(a);
	set_current_position(b);
	set_target_a(a, b);
	set_cost_a(a, b);
	set_cheapest(a);
}

/*
 * Entrada principal do algoritmo turk: empurra elementos de A para B,
 * ordena os 3 últimos em A e depois devolve B -> A na ordem correta.
 */
void	turk_sort(t_stack **a, t_stack **b)
{
	push_two_to_b(a, b);
	push_a_to_b_until_three(a, b);
	sort_three(a);
	push_b_to_a_all(a, b);
	set_current_position(*a);
	min_on_top(a);
}
