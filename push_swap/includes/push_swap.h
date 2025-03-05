/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:30:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/05 12:05:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_stack
{
	int				item;
	int				index;
	struct s_stack	*next;
}	t_stack;

/* Sorting out functions */
int		sort_nbr(char *str, t_stack **stack);
int		sort_arg(char *arg, t_stack **stack);
t_stack	*sort_input(int ac, char **av);

/* Util functions */
int		if_sorted(t_stack *stack);
int		safe_atoi(char *str, int *error);
int		check_digit(char *str);
int		check_dup(t_stack *stack);
void	free_if_error(t_stack **stack);
void	add_node(t_stack **stack, int element);
t_stack	*create_node(int element);

/* Algorithm utils */

/* Instruction functions */
void	swap(t_stack **stack);
void	push(t_stack **src, t_stack **dest);
void	rotate(t_stack **stack);
void	reverse_rotate(t_stack **stack);

void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

#endif
