/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicort <danicort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by danicort          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by danicort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);

void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **b, t_stack **a);

void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);

void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

/* Turk algorithm helpers */
void	turk_sort(t_stack **a, t_stack **b);
void	init_nodes_a(t_stack *a, t_stack *b);
void	set_cheapest(t_stack *stack);

int		max_int(int a, int b);

void	set_current_position(t_stack *stack);
void	set_target_a(t_stack *a, t_stack *b);
void	set_cost_a(t_stack *a, t_stack *b);
void	set_target_b(t_stack *b, t_stack *a);
void	set_cost_b(t_stack *b, t_stack *a);
void	move_a_to_b(t_stack **a, t_stack **b);
void	init_nodes_b(t_stack *a, t_stack *b);
void	move_b_to_a(t_stack **a, t_stack **b);
void	min_on_top(t_stack **a);

/* Small sorts and utilities */
void	sort_three(t_stack **a);

void	init_stack_a(t_stack **a, char **argv);

void	free_stack(t_stack **stack);
int		stack_len(t_stack *stack);
t_stack	*find_last(t_stack *stack);
t_stack	*find_min(t_stack *stack);
t_stack	*find_max(t_stack *stack);
bool	is_sorted(t_stack *stack);
void	append_node(t_stack **stack, int n);
bool	check_duplicate(t_stack *stack, int value);

/* parsing helpers */
char	**split_ws(const char *s);
void	free_split(char **arr);
int		is_space(char c);
int		count_words(const char *s);
void	free_arr_on_error(char **arr, int j);
bool	is_valid_int_token(const char *s);

#endif
