/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/08 09:47:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	int				push_cost;
	bool			above_median;
	bool			cheapest;
	struct s_stack	*target_node;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

/* Commands */
void	sa(t_stack **a, int print);
void	sb(t_stack **b, int print);
void	ss(t_stack **a, t_stack **b, int print);

void	pa(t_stack **a, t_stack **b, int print);
void	pb(t_stack **a, t_stack **b, int print);

void	ra(t_stack **a, int print);
void	rb(t_stack **b, int print);
void	rr(t_stack **a, t_stack **b, int print);

void	rra(t_stack **a, int print);
void	rrb(t_stack **b, int print);
void	rrr(t_stack **a, t_stack **b, int print);

/* Turk algorithm helpers */
void	turk_sort(t_stack **a, t_stack **b);
void	init_nodes_a(t_stack *a, t_stack *b);
void	init_nodes_b(t_stack *a, t_stack *b);
void	move_a_to_b(t_stack **a, t_stack **b);
void	move_b_to_a(t_stack **a, t_stack **b);
t_stack	*get_cheapest(t_stack *stack);

/* Turk algorithm - cost/target calculation */
void	set_current_position(t_stack *stack);
void	set_target_a(t_stack *a, t_stack *b);
void	set_cost_a(t_stack *a, t_stack *b);
void	set_cheapest(t_stack *stack);
void	set_target_b(t_stack *b, t_stack *a);

/* Small sorts and final rotation */
void	sort_three(t_stack **a);
void	min_on_top(t_stack **a);

/* Stack initialization and validation */
void	init_stack_a(t_stack **a, char **argv);
bool	is_valid_int_token(const char *s);
void	free_stack(t_stack **stack);
bool	check_duplicate(t_stack *stack, int value);
void	append_node(t_stack **stack, int n);

/* Stack utils */
int		stack_len(t_stack *stack);
t_stack	*stack_last(t_stack *stack);
t_stack	*find_min(t_stack *stack);
t_stack	*find_max(t_stack *stack);
bool	is_sorted(t_stack *stack);
int		max_int(int a, int b);

/* String parsing (split) */
char	**split_ws(const char *s);
void	free_split(char **arr);
int		is_space(char c);
int		count_words(const char *s);
void	free_arr_on_error(char **arr, int j);

#endif
