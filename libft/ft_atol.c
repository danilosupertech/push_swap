/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <limits.h>

/*
 * Retorna valor saturado em overflow conforme o sinal.
 * static porque é helper interno do ft_atol().
 */
static long	overflow_ret(int sign)
{
	if (sign < 0)
		return (LONG_MIN);
	return (LONG_MAX);
}

/*
 * Lê um sinal opcional (+/-) e avança o ponteiro.
 * static porque é helper interno do ft_atol().
 */
static int	parse_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

/* Converte string numérica para long, saturando em overflow. */
long	ft_atol(const char *s)
{
	unsigned long	res;
	unsigned long	limit;
	unsigned long	digit;
	int				sign;

	if (!s)
		return (0);
	sign = parse_sign(&s);
	res = 0;
	limit = (unsigned long)LONG_MAX + (unsigned long)(sign < 0);
	while (*s >= '0' && *s <= '9')
	{
		digit = (unsigned long)(*s - '0');
		if (res > limit / 10UL || (res == limit / 10UL && digit > limit % 10UL))
			return (overflow_ret(sign));
		res = res * 10UL + digit;
		s++;
	}
	if (sign < 0 && res == (unsigned long)LONG_MAX + 1UL)
		return (LONG_MIN);
	return ((long)res * (long)sign);
}
