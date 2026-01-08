/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rev_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Faz rotação reversa: o último elemento vira o primeiro.
 * static porque é um helper interno usado por rra, rrb e rrr.
 */
static void	rev_rotate(t_stack **s)
{
	t_stack	*last;
	t_stack	*before_last;

	if (!s || !*s || !(*s)->next)
		return ;
	last = find_last(*s);
	before_last = last->prev;
	before_last->next = NULL;
	last->prev = NULL;
	last->next = *s;
	(*s)->prev = last;
	*s = last;
}

/*
 * rra: Rotação reversa em A (último vira primeiro).
 */
void	rra(t_stack **a)
{
	rev_rotate(a);
	write(1, "rra\n", 4);
}

/*
 * rrb: Rotação reversa em B (último vira primeiro).
 */
void	rrb(t_stack **b)
{
	rev_rotate(b);
	write(1, "rrb\n", 4);
}

/*
 * rrr: Rotação reversa em A e B ao mesmo tempo.
 */
void	rrr(t_stack **a, t_stack **b)
{
	rev_rotate(a);
	rev_rotate(b);
	write(1, "rrr\n", 4);
}
