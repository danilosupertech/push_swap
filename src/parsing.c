/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	count_words(const char *s)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s && *s)
	{
		if (is_space(*s))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

void	free_arr_on_error(char **arr, int j)
{
	int	k;

	k = 0;
	while (k < j)
	{
		free(arr[k]);
		k++;
	}
	free(arr);
}

void	free_split(char **arr)
{
	int	k;

	if (!arr)
		return ;
	k = 0;
	while (arr[k])
	{
		free(arr[k]);
		k++;
	}
	free(arr);
}

char	**split_ws(const char *s)
{
	char		**out;
	int			words;
	int			i;
	int			start;
	int			len;

	if (!s)
		return (NULL);
	words = count_words(s);
	out = (char **)malloc(sizeof(char *) * (words + 1));
	if (!out)
		return (NULL);
	i = 0;
	start = -1;
	while (*s)
	{
		if (!is_space(*s) && start < 0)
			start = 0;
		if (start >= 0)
			start++;
		if ((is_space(*s) || *(s + 1) == '\0') && start > 0)
		{
			len = start - (is_space(*s) ? 1 : 0);
			out[i] = ft_substr(s - start + 1, 0, len);
			if (!out[i])
			{
				free_arr_on_error(out, i);
				return (NULL);
			}
			i++;
			start = -1;
		}
		s++;
	}
	out[i] = NULL;
	return (out);
}
