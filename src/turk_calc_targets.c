/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_calc_targets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Em B, encontra o melhor target para inserir um valor vindo de A:
 * o maior valor < val; se não existir, usa o max de B.
 * static porque é um helper interno usado só neste ficheiro.
 */
static t_stack	*find_target_in_b(t_stack *b, int val)
{
	t_stack	*best;
	t_stack	*it;

	if (!b)
		return (NULL);
	best = NULL;
	it = b;
	while (it)
	{
		if (it->value < val)
			if (!best || it->value > best->value)
				best = it;
		it = it->next;
	}
	if (best)
		return (best);
	return (find_max(b));
}

/*
 * Para cada nó de A, define target_node em B (onde ele deve ser inserido).
 */
void	set_target_a(t_stack *a, t_stack *b)
{
	t_stack	*tmp;

	tmp = a;
	while (tmp)
	{
		tmp->target_node = find_target_in_b(b, tmp->value);
		tmp = tmp->next;
	}
}

/*
 * Em A, encontra o melhor target para inserir um valor vindo de B:
 * o menor valor > val; se não existir, usa o min de A.
 * static porque é um helper interno usado só neste ficheiro.
 */
static t_stack	*find_target_in_a(t_stack *a, int val)
{
	t_stack	*best;
	t_stack	*it;

	if (!a)
		return (NULL);
	best = NULL;
	it = a;
	while (it)
	{
		if (it->value > val)
		{
			if (!best || it->value < best->value)
				best = it;
		}
		it = it->next;
	}
	if (best)
		return (best);
	return (find_min(a));
}

/*
 * Para cada nó de B, define target_node em A (onde ele deve ser inserido).
 */
void	set_target_b(t_stack *b, t_stack *a)
{
	t_stack	*tmp;

	tmp = b;
	while (tmp)
	{
		tmp->target_node = find_target_in_a(a, tmp->value);
		tmp = tmp->next;
	}
}
