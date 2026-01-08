/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Troca os 2 primeiros elementos no topo de uma stack.
 * Não faz nada se houver 0 ou 1 elementos.
 */
static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	first->prev = second;
	second->next = first;
	*stack = second;
}

/*
 * Troca os 2 primeiros elementos no topo da stack a.
 * Imprime "sa" na saída padrão.
 */
void	sa(t_stack **a, int print)
{
	swap(a);
	if (print)
		ft_putstr_fd("sa\n", 1);
}

/*
 * Troca os 2 primeiros elementos no topo da stack b.
 * Imprime "sb" na saída padrão.
 */
void	sb(t_stack **b, int print)
{
	swap(b);
	if (print)
		ft_putstr_fd("sb\n", 1);
}

/*
 * sa e sb ao mesmo tempo.
 * Imprime "ss" na saída padrão.
 */
void	ss(t_stack **a, t_stack **b, int print)
{
	swap(a);
	swap(b);
	if (print)
		ft_putstr_fd("ss\n", 1);
}
