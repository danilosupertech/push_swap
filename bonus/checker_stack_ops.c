/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_stack_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Troca os dois primeiros elementos da stack s (sem output). */
void	chk_swap_top(t_stack **s)
{
	t_stack	*first;
	t_stack	*second;

	if (!s || !*s || !(*s)->next)
		return ;
	first = *s;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*s = second;
}

/* Empurra o topo de src para dst (sem output). */
void	chk_push_top(t_stack **dst, t_stack **src)
{
	t_stack	*n;

	if (!src || !*src)
		return ;
	n = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	n->prev = NULL;
	n->next = *dst;
	if (*dst)
		(*dst)->prev = n;
	*dst = n;
}

/* Rotaciona a stack s (primeiro vira último), sem output. */
void	chk_rotate_stack(t_stack **s)
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

/* Faz rotação reversa na stack s (último vira primeiro), sem output. */
void	chk_rev_rotate_stack(t_stack **s)
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
