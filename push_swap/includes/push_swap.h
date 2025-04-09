/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:17:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 14:08:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

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

/* Stack */
t_stack	*init_stack(void);
void	free_stack(t_stack *stack);
void	push_to(t_stack *stack, int value);
int		pop(t_stack *stack);

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

/* Parcing */
void	parse_args(t_stack *a, char **av);
int		is_valid_number(char *str);
int		is_duplicate(t_stack *stack, int value);

/* Sort */
void	sort_three(t_stack *a);
void	sort_five(t_stack *a, t_stack *b);
void	sort_small(t_stack *a, t_stack *b);
void	turk_sort(t_stack *a, t_stack *b);

/* Sort utils */
void	ft_sort_int_tab(int *tab, int size);
void	final_rotate(t_stack *a);
void	move_to_position(t_stack *stack, int pos, int direction);

/* Utils */
t_node	*new_node(int value);
int		is_sorted(t_stack *stack);
void	if_error(const char *str);
int		find_min(t_stack *stack);
int		find_target_position(t_stack *a, int value);

#endif
