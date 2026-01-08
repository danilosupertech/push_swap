/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

/*
 * Preenche o array `arr` com substrings (tokens) separados por whitespace.
 * Retorna o número de tokens ou -1 em caso de erro.
 * static porque é um detalhe interno do split_ws().
 */
static int	fill_tokens(const char *s, char **arr)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		start = i;
		while (s[i] && !is_space(s[i]))
			i++;
		if (i > start)
		{
			arr[j] = ft_substr(s, (unsigned int)start, (size_t)(i - start));
			if (!arr[j])
				return (free_arr_on_error(arr, j), -1);
			j++;
		}
	}
	arr[j] = NULL;
	return (j);
}

/*
 * Faz split por whitespace. Retorna um array NULL-terminated de strings.
 * Em caso de erro de alocação, retorna NULL.
 */
char	**split_ws(const char *s)
{
	char	**arr;
	int		words;

	words = count_words(s);
	arr = (char **)ft_calloc((size_t)words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	if (fill_tokens(s, arr) < 0)
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
