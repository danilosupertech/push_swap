/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Rotaciona uma stack: o primeiro elemento vira o último.
 * static porque é um helper interno usado por ra, rb e rr.
 */
static void	rotate(t_stack **s)
{
	t_stack	*first;
	t_stack	*last;

	if (!s || !*s || !(*s)->next)
		return ;
	first = *s;
	last = find_last(*s);
	*s = first->next;
	(*s)->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
}

/*
 * ra: Rotaciona A (primeiro vira último).
 */
void	ra(t_stack **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

/*
 * rb: Rotaciona B (primeiro vira último).
 */
void	rb(t_stack **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

/*
 * rr: Rotaciona A e B ao mesmo tempo.
 */
void	rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}
