/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Desloca para cima todos os elementos de uma stack por 1.
 * O primeiro elemento se torna o último.
 */
static void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = stack_last(*stack);
	*stack = first->next;
	(*stack)->prev = NULL;
	first->next = NULL;
	first->prev = last;
	last->next = first;
}

/*
 * Desloca para cima todos os elementos da stack a por 1.
 * Imprime "ra" na saída padrão.
 */
void	ra(t_stack **a, int print)
{
	rotate(a);
	if (print)
		ft_putstr_fd("ra\n", 1);
}

/*
 * Desloca para cima todos os elementos da stack b por 1.
 * Imprime "rb" na saída padrão.
 */
void	rb(t_stack **b, int print)
{
	rotate(b);
	if (print)
		ft_putstr_fd("rb\n", 1);
}

/*
 * ra e rb ao mesmo tempo.
 * Imprime "rr" na saída padrão.
 */
void	rr(t_stack **a, t_stack **b, int print)
{
	rotate(a);
	rotate(b);
	if (print)
		ft_putstr_fd("rr\n", 1);
}
