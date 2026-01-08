/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Pega o primeiro elemento do topo da stack `src` e o coloca no topo
 * da stack `dst`. Não faz nada se `src` estiver vazia.
 */
static void	push(t_stack **dst, t_stack **src)
{
	t_stack	*node_to_push;

	if (!src || !*src)
		return ;
	node_to_push = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node_to_push->prev = NULL;
	if (!*dst)
	{
		*dst = node_to_push;
		node_to_push->next = NULL;
	}
	else
	{
		node_to_push->next = *dst;
		(*dst)->prev = node_to_push;
		*dst = node_to_push;
	}
}

/*
 * Pega o primeiro elemento do topo da stack b e o coloca no topo da stack a.
 * Imprime "pa" na saída padrão.
 */
void	pa(t_stack **a, t_stack **b, int print)
{
	push(a, b);
	if (print)
		ft_putstr_fd("pa\n", 1);
}

/*
 * Pega o primeiro elemento do topo da stack a e o coloca no topo da stack b.
 * Imprime "pb" na saída padrão.
 */
void	pb(t_stack **a, t_stack **b, int print)
{
	push(b, a);
	if (print)
		ft_putstr_fd("pb\n", 1);
}
