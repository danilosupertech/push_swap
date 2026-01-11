/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 15:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** String Splitting and Tokenization
**
** Handles parsing of whitespace-separated input strings:
**
** - is_space: Detects whitespace characters
** - count_words: Counts whitespace-separated tokens
** - split_ws: Splits string by whitespace into token array
** - process_word: Internal helper for word extraction
**
** Supports both individual arguments and quoted strings with multiple
** numbers (e.g., ./push_swap "3 2 1").
** Memory deallocation handled by parse_split_free.c.
*/

/*
** Checks if a character is whitespace.
**
** @param c: Character to check
** @return: 1 if whitespace, 0 otherwise
*/
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

/*
** Counts the number of whitespace-separated words in a string.
**
** @param s: String to analyze
** @return: Number of words (tokens)
*/
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

/*
** Internal helper: extracts and stores a word when delimiter is found.
**
** @param out: Output array to store extracted word
** @param s: Pointer to current position in input string
** @param i: Pointer to current index in output array
** @param start: Pointer to word start position tracker
*/
static void	process_word(char **out, const char **s, int *i, int *start)
{
	int	len;

	if (is_space(**s) || *(*s + 1) == '\0')
	{
		if (*start > 0)
		{
			if (is_space(**s))
				len = *start - 1;
			else
				len = *start;
			out[(*i)] = ft_substr(*s - *start + 1, 0, len);
			if (!out[(*i)])
				free_arr_on_error(out, *i);
			else
				(*i)++;
			*start = -1;
		}
	}
}

/*
** Splits a string by whitespace into a null-terminated array of strings.
**
** @param s: String to split
** @return: Null-terminated array of words, or NULL on error
*/
char	**split_ws(const char *s)
{
	char	**out;
	int		i;
	int		start;

	if (!s)
		return (NULL);
	out = (char **)malloc(sizeof(char *) * (count_words(s) + 1));
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
		process_word(out, &s, &i, &start);
		s++;
	}
	out[i] = NULL;
	return (out);
}
