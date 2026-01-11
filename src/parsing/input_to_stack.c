/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Input to Stack Conversion
**
** Orchestrates the entire input parsing and stack construction process.
** Takes command-line arguments, validates them, and builds stack A.
**
** Process:
** 1. Split each argument by whitespace
** 2. Validate each token (format, range, duplicates)
** 3. Convert to integer and append to stack
** 4. Handle errors by freeing resources and exiting
**
** Supports both separate arguments and quoted strings:
** - ./push_swap 3 2 1
** - ./push_swap "3 2 1"
*/

/*
** Handles errors by freeing resources, printing "Error" and exiting.
**
** @param a: Stack to free
** @param split: String array to free (if any)
*/
static void	error_exit(t_stack **a, char **split)
{
	if (split)
		free_split(split);
	free_stack(a);
	write(2, "Error\n", 6);
	exit(1);
}

/*
** Validates a token, converts it to integer, checks for duplicates,
** and adds it to stack A. Exits on any validation failure.
**
** @param a: Pointer to stack A
** @param token: String token to parse
** @param split_ctx: Current split array (for cleanup on error)
*/
static void	parse_and_add(t_stack **a, const char *token, char **split_ctx)
{
	long	n;

	if (!is_valid_int_token(token))
		error_exit(a, split_ctx);
	n = ft_atol(token);
	if (n > INT_MAX || n < INT_MIN)
		error_exit(a, split_ctx);
	if (check_duplicate(*a, (int)n))
		error_exit(a, split_ctx);
	append_node(a, (int)n);
}

/*
** Initializes stack A from command-line arguments.
** Handles both individual arguments and whitespace-separated strings.
**
** @param a: Pointer to stack A pointer
** @param argv: Array of argument strings (NULL-terminated)
*/
void	init_stack_a(t_stack **a, char **argv)
{
	int		i;
	int		j;
	char	**split;

	if (!a || !argv)
		return ;
	i = 0;
	while (argv[i])
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			error_exit(a, NULL);
		if (!split[0])
			error_exit(a, split);
		j = 0;
		while (split[j])
		{
			parse_and_add(a, split[j], split);
			j++;
		}
		free_split(split);
		i++;
	}
}
