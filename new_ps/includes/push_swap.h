/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:40:46 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 19:46:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*prev;
	struct s_node	*next;
}			t_node;

typedef struct s_stack
{
	int		size;
	t_node	*head;
	t_node	*tail;
}			t_stack;

/* Init */
t_stack	*init_stack(void);
t_node	*create_node(int value);
void	free_stack(t_stack *stack);
void	add_node_front(t_stack *stack, t_node *new_node);
void	add_node_back(t_stack *stack, t_node *new_node);

/* Parsing */
void	parse_fill_stack(int ac, char **av, t_stack *stack_a);

/* Operations */
/* Swap */
void	sa(t_stack *stack_a);
void	sb(t_stack *stack_b);
void	ss(t_stack *stack_a, t_stack *stack_b);
/* Push */
void	pa(t_stack *stack_a, t_stack *stack_b);
void	pb(t_stack *stack_a, t_stack *stack_b);
/* Rotate */
void	ra(t_stack *stack_a);
void	rb(t_stack *stack_b);
void	rr(t_stack *stack_a, t_stack *stack_b);
/* Reverse rotate */
void	rra(t_stack *stack_a);
void	rrb(t_stack *stack_b);
void	rrr(t_stack *stack_a, t_stack *stack_b);

/* Sorting */
void	sort_two(t_stack *stack_a);
void	sort_three(t_stack *stack_a);
void	sort_four(t_stack *stack_a, t_stack *stack_b);
void	sort_five(t_stack *stack_a, t_stack *stack_b);
void	sort_large(t_stack *stack_a, t_stack *stack_b);;

/* Sorting utils */
bool	is_sorted(t_stack *stack);
t_node	*find_node_by_idx(t_stack *stack, int idx);
t_node	*find_cheapest_node(t_stack *stack, int max_idx);
int		node_position(t_stack *stack, t_node *node_to_find);
void	node_to_top_a(t_stack *stack_a, t_node *target_node);
void	node_to_top_b(t_stack *stack_b, t_node *target_node);

/* Index utils */
void	assign_index(t_stack *stack_a);

/* Utils */
bool	is_num(const char *str);
void	error_exit(t_stack *stack_a, t_stack *stack_b);


#endif