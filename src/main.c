/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:48:48 by danicort          #+#    #+#             */
/*   Updated: 2026/01/10 11:01:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Push_Swap Main Entry Point
**
** This is the main program that sorts a stack of integers using the minimum
** number of operations. It accepts integers as command-line arguments and
** outputs the sequence of operations needed to sort them.
**
** Usage: ./push_swap [numbers...]
** Example: ./push_swap 3 2 1 0 -> outputs operations to sort
**
** Allowed operations:
** - sa/sb/ss: swap first two elements
** - pa/pb: push from one stack to another
** - ra/rb/rr: rotate up (first becomes last)
** - rra/rrb/rrr: reverse rotate down (last becomes first)
**
** The program uses the Turk algorithm for efficient sorting.
*/

/*
** Main function: parses input, sorts if needed, and cleans up.
**
** @param argc: Argument count
** @param argv: Argument values (integers to sort)
** @return: 0 on success
*/

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	init_stack_a(&a, argv + 1);
	if (stack_len(a) > 1 && !is_sorted(a))
		turk_sort(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
