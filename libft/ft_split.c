/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/11 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** String Splitting Utility
**
** Splits a string into an array of substrings based on a delimiter character.
** Allocates memory for the result array and each substring.
**
** - count_words: Counts the number of words separated by delimiter
** - word_length: Calculates the length of the next word
** - free_split: Deallocates split array on error
** - ft_split: Main function to split string into array
**
** Essential for parsing command-line arguments and handling multiple values.
*/

/*
** Counts the number of words in a string separated by delimiter c.
**
** @param s: String to analyze
** @param c: Delimiter character
** @return: Number of words found
*/
static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

/*
** Calculates the length of the next word starting at s, delimited by c.
**
** @param s: String pointer at start of word
** @param c: Delimiter character
** @return: Length of the word
*/
static int	word_length(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

/*
** Frees allocated memory for split array on error.
** Used to clean up partial allocations if malloc fails during splitting.
**
** @param split: Array to deallocate
** @param j: Number of strings to free
** @return: NULL
*/
static char	**free_split(char **split, int j)
{
	while (j > 0)
		free(split[--j]);
	free(split);
	return (NULL);
}

/*
** Fills the split array by iterating through the string and extracting words.
**
** @param split: Array to fill
** @param s: String to split (pointer will be modified)
** @param c: Delimiter character
** @return: 0 on success, -1 on allocation failure
*/
static int	fill_split(char **split, const char **s, char c)
{
	int	j;

	j = 0;
	while (**s)
	{
		if (**s != c)
		{
			split[j] = ft_substr(*s, 0, word_length(*s, c));
			if (!split[j])
				return (-1);
			j++;
			while (**s && **s != c)
				(*s)++;
		}
		else
			(*s)++;
	}
	split[j] = NULL;
	return (0);
}

/*
** Allocates and fills an array of strings by splitting s at each delimiter c.
** Result is NULL-terminated array.
**
** @param s: String to split
** @param c: Delimiter character
** @return: Array of strings, or NULL on allocation failure
*/
char	**ft_split(const char *s, char c)
{
	char	**split;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	split = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (fill_split(split, &s, c) == -1)
		return (free_split(split, word_count));
	return (split);
}
