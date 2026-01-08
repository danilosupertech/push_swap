/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
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
 * Valida se `s` é um token inteiro no formato [+|-]?[0-9]+.
 */
bool	is_valid_int_token(const char *s)
{
	int	i;

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
	return (true);
}
