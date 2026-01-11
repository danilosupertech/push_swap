/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/10 11:01:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <limits.h>

/*
** Returns saturated value on overflow according to sign.
** Static helper function internal to ft_atol().
*/

static long	overflow_ret(int sign)
{
	if (sign < 0)
		return (LONG_MIN);
	return (LONG_MAX);
}

/*
** Reads optional sign (+/-) and advances the pointer.
** Static helper function internal to ft_atol().
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

/*
** Converts numeric string to long, saturating on overflow.
*/

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
