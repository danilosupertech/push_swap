/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Input Validation
**
** Validates input tokens to ensure they represent valid integers and
** detects duplicates before adding to the stack.
**
** - is_valid_int_token: Checks if a string is a valid integer within range
** - check_duplicate: Searches stack for duplicate values
**
** These functions prevent invalid input from causing errors and ensure
** the stack contains only unique, valid integers.
*/

/*
** Validates if a string represents a valid integer within INT_MIN/INT_MAX.
** Accepts optional leading '+' or '-' sign.
**
** @param s: String to validate
** @return: true if valid integer, false otherwise
*/
bool	is_valid_int_token(const char *s)
{
	long	val;
	int		i;

	if (!s || !*s)
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (false);
		i++;
	}
	val = ft_atol(s);
	if (val < INT_MIN || val > INT_MAX)
		return (false);
	return (true);
}

/*
** Checks if a value already exists in the stack.
**
** @param stack: Stack to search
** @param value: Value to check for
** @return: true if duplicate found, false otherwise
*/
bool	check_duplicate(t_stack *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (true);
		stack = stack->next;
	}
	return (false);
}
