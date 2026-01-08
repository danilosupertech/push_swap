/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 09:46:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/libft.h"

/*
 * Finaliza o programa com erro: libera recursos, imprime "Error\n" e sai(1).
 * static porque é um helper local, usado apenas neste ficheiro.
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
 * Valida um token, converte para int e adiciona na stack A.
 * static porque só é chamado pelo loop de init_stack_a().
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
 * Inicializa a stack A a partir dos argumentos.
 * Aceita tanto argv separado (ex.: "./push_swap 1 2 3") quanto string
 * com espaços
 * (ex.: "./push_swap \"1 2 3\"").
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
		split = split_ws(argv[i]);
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
