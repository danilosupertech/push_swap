/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Retorna o maior entre dois inteiros. */
int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
 * Inicializa campos auxiliares dos nós em B: posição atual, target em A,
 * custo de push e flag cheapest.
 */
void	init_nodes_b(t_stack *a, t_stack *b)
{
	set_current_position(a);
	set_current_position(b);
	set_target_b(b, a);
	set_cost_b(b, a);
	set_cheapest(b);
}
