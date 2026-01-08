/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * pa: Empurra o topo de B para o topo de A.
 * Assinatura: pa(t_stack **a, t_stack **b) (destino, origem).
 */
void	pa(t_stack **a, t_stack **b)
{
	t_stack	*push_node;

	if (!b || !*b)
		return ;
	push_node = *b;
	*b = (*b)->next;
	if (*b)
		(*b)->prev = NULL;
	push_node->prev = NULL;
	if (!*a)
	{
		*a = push_node;
		push_node->next = NULL;
	}
	else
	{
		push_node->next = *a;
		(*a)->prev = push_node;
		*a = push_node;
	}
	write(1, "pa\n", 3);
}

/*
 * pb: Empurra o topo de A para o topo de B.
 * Nota: por convenção do projeto, pb tem assinatura "invertida":
 * pb(t_stack **b, t_stack **a) (destino, origem), para chamar como pb(b, a).
 */
void	pb(t_stack **b, t_stack **a)
{
	t_stack	*push_node;

	if (!a || !*a)
		return ;
	push_node = *a;
	*a = (*a)->next;
	if (*a)
		(*a)->prev = NULL;
	push_node->prev = NULL;
	if (!*b)
	{
		*b = push_node;
		push_node->next = NULL;
	}
	else
	{
		push_node->next = *b;
		push_node->next->prev = push_node;
		*b = push_node;
	}
	write(1, "pb\n", 3);
}
