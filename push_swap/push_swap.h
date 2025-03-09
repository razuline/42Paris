/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:17:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/09 09:45:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct	s_node
{
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}				t_node;

typedef struct	s_stack
{
	int		size;
	t_node	*head;
	t_node	*tail;
}				t_stack;

/* Stack's functions */
t_stack	*init_stack(void);
void	free_stack(t_stack *stack);
void	push_to(t_stack *stack, int value);
int		pop(t_stack *stack);
void	parse_input(t_stack *stack, char **av);

/* Sort functions */
t_node	*find_min(t_stack *stack);
void	sort_three(t_stack *a);
void	sort_small(t_stack *a, t_stack *b);

/* Turk sort alghoritm */
int		max_bits(t_stack *stack);
void	turk_sort(t_stack *a, t_stack *b);

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

/* Utils */
void	if_error(const char *str);
void	parse_args(t_stack *a, char **av);
t_node	*new_node(int value);

#endif
