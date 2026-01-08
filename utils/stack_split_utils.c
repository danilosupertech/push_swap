/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Retorna 1 se `c` for whitespace (espaço ou \t/\n/\v/\f/\r).
 */
int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/*
 * Conta quantas palavras (tokens) existem em `s`, separadas por whitespace.
 */
int	count_words(const char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_space(s[i]))
			i++;
	}
	return (count);
}

/*
 * Libera um array NULL-terminated de strings e o próprio array.
 */
void	free_split(char **arr)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
 * Libera parcialmente `arr` (do índice 0 até j-1) após erro de alocação.
 */
void	free_arr_on_error(char **arr, int j)
{
	int	k;

	k = 0;
	while (k < j)
	{
		free(arr[k]);
		k++;
	}
}
