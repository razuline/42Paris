/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:17:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 16:59:17 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef struct s_node
{
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}			t_node;

typedef struct s_stack
{
	int		size;
	t_node	*head;
	t_node	*tail;
}			t_stack;

/* Operations */
void	swap(t_stack *stack);
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);

void	push(t_stack *dst, t_stack *src);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

void	rotate(t_stack *stack);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);

void	reverse_rotate(t_stack *stack);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/* Small sort */
void	sort_three(t_stack *a);
void	sort_four(t_stack *a, t_stack *b);
void	sort_five(t_stack *a, t_stack *b);
void	small_sort(t_stack *a, t_stack *b);
void	chunk_sort(t_stack *a, t_stack *b);

/* Positions */
int		find_min(t_stack *stack);
int		find_min_pos(t_stack *stack);
int		find_second_min(t_stack *stack);
int		find_target_pos(t_stack *a, int val);
void	while_pos(t_stack *s, int pos, int rev);

/* Parcing */
void	parse_args(t_stack *a, t_stack *b, char **av);
long	push_swap_atol(const char *str, t_stack *a, t_stack *b);
int		is_duplicate(t_stack *a, int num);
void	add_node(t_stack *stack, int value);

/* Utils */
int		is_sorted(t_stack *stack);
int		is_valid_number(char *str);
void	final_rotate(t_stack *a);
void	free_stack(t_stack *stack);
void	free_split(char **split);
void	error_exit(t_stack *a, t_stack *b);

#endif
