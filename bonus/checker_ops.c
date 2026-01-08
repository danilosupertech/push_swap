/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

void	chk_swap_top(t_stack **s);
void	chk_push_top(t_stack **dst, t_stack **src);
void	chk_rotate_stack(t_stack **s);
void	chk_rev_rotate_stack(t_stack **s);

/*
 * Retorna 1 se op == lit (match exato), senão 0.
 * static porque é um helper local de dispatch.
 */
static int	op_eq(const char *op, const char *lit)
{
	size_t	len;

	len = ft_strlen(lit);
	if (ft_strncmp(op, lit, len) != 0)
		return (0);
	return (op[len] == '\0');
}

/*
 * Liberta stacks, imprime Error no stderr e sai com status 1.
 * static porque é um helper interno deste ficheiro.
 */
static void	error_and_exit(t_stack **a, t_stack **b)
{
	free_stack(a);
	free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}

/*
 * Aplica instruções sa/sb/ss/pa/pb; retorna 1 se a op foi tratada.
 * static porque é uma etapa interna do apply_op().
 */
static int	apply_swap_push(const char *op, t_stack **a, t_stack **b)
{
	if (op_eq(op, "sa"))
		chk_swap_top(a);
	else if (op_eq(op, "sb"))
		chk_swap_top(b);
	else if (op_eq(op, "ss"))
	{
		chk_swap_top(a);
		chk_swap_top(b);
	}
	else if (op_eq(op, "pa"))
		chk_push_top(a, b);
	else if (op_eq(op, "pb"))
		chk_push_top(b, a);
	else
		return (0);
	return (1);
}

/*
 * Aplica instruções (r)r(a|b) e (r)rr; retorna 1 se tratada.
 * static porque é uma etapa interna do apply_op().
 */
static int	apply_rotate(const char *op, t_stack **a, t_stack **b)
{
	if (op_eq(op, "ra"))
		chk_rotate_stack(a);
	else if (op_eq(op, "rb"))
		chk_rotate_stack(b);
	else if (op_eq(op, "rr"))
	{
		chk_rotate_stack(a);
		chk_rotate_stack(b);
	}
	else if (op_eq(op, "rra"))
		chk_rev_rotate_stack(a);
	else if (op_eq(op, "rrb"))
		chk_rev_rotate_stack(b);
	else if (op_eq(op, "rrr"))
	{
		chk_rev_rotate_stack(a);
		chk_rev_rotate_stack(b);
	}
	else
		return (0);
	return (1);
}

/* Executa uma instrução; dá erro se a op for inválida. */
void	apply_op(const char *op, t_stack **a, t_stack **b)
{
	if (apply_swap_push(op, a, b))
		return ;
	if (apply_rotate(op, a, b))
		return ;
	error_and_exit(a, b);
}
