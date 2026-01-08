/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Desloca para baixo todos os elementos de uma stack por 1.
 * O último elemento se torna o primeiro.
 */
static void	rev_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	last = stack_last(*stack);
	second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	last->next = *stack;
	(*stack)->prev = last;
	*stack = last;
}

/*
 * Desloca para baixo todos os elementos da stack a por 1.
 * Imprime "rra" na saída padrão.
 */
void	rra(t_stack **a, int print)
{
	rev_rotate(a);
	if (print)
		ft_putstr_fd("rra\n", 1);
}

/*
 * Desloca para baixo todos os elementos da stack b por 1.
 * Imprime "rrb" na saída padrão.
 */
void	rrb(t_stack **b, int print)
{
	rev_rotate(b);
	if (print)
		ft_putstr_fd("rrb\n", 1);
}

/*
 * rra e rrb ao mesmo tempo.
 * Imprime "rrr" na saída padrão.
 */
void	rrr(t_stack **a, t_stack **b, int print)
{
	rev_rotate(a);
	rev_rotate(b);
	if (print)
		ft_putstr_fd("rrr\n", 1);
}
