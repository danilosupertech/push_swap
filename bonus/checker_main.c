/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	apply_op(const char *op, t_stack **a, t_stack **b);

/*
 * Liberta stacks, imprime Error no stderr e sai com status 1.
 * static porque é um helper interno usado só neste ficheiro.
 */
static void	error_exit(t_stack **a, t_stack **b)
{
	free_stack(a);
	free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}

/*
 * Lê uma instrução para op (máx 4 chars, sem '\n').
 * static porque é parte do IO interno do checker.
 */
static int	read_op_line(int fd, char op[5])
{
	char	c;
	int		i;
	int		r;

	i = 0;
	while (1)
	{
		r = (int)read(fd, &c, 1);
		if (r < 0)
			return (-1);
		if (r == 0)
			break ;
		if (c == '\n')
			break ;
		if (i >= 4)
			return (-2);
		op[i++] = c;
	}
	if (i == 0 && r == 0)
		return (0);
	op[i] = '\0';
	return (1);
}

/*
 * Descarta caracteres até '\n' ou EOF (linhas longas demais).
 * static porque é um detalhe de robustez do reader.
 */
static void	drain_to_eol(int fd)
{
	char	c;

	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
	}
}

/*
 * Lê e aplica todas as operações do stdin até EOF.
 * static porque só é usado pela main() deste ficheiro.
 */
static void	run_ops(t_stack **a, t_stack **b)
{
	char	op[5];
	int		res;

	while (1)
	{
		res = read_op_line(0, op);
		if (res == 0)
			return ;
		if (res < 0)
		{
			if (res == -2)
				drain_to_eol(0);
			error_exit(a, b);
		}
		apply_op(op, a, b);
	}
}

/* checker entrypoint: parse args, read ops from stdin, print OK/KO. */
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = NULL;
	b = NULL;
	init_stack_a(&a, argv + 1);
	run_ops(&a, &b);
	if (b == NULL && is_sorted(a))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
