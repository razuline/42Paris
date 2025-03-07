/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:30:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/07 11:18:55 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct	s_stack
{
	int				number;
	struct s_stack	*next;
}	t_stack;

/* Sorting functions */
void	sort_two(t_stack **stack);
void	sort_three(t_stack **stack);
void	sort_five(t_stack **stack);

/* Stack functions */
void	push(t_stack **stack, int num);
int		pop(t_stack **stack);
int		stack_size(t_stack *stack);
int		if_stack_empty(t_stack *stack);

/* Util functions */
int	*if_valid_input(int ac, char **av, int *size);

/* Algorithm utils */

/* Instructions */
void	swap(t_stack **stack);
void	push(t_stack **stack, int num);
void	rotate(t_stack **stack);
void	reverse_rotate(t_stack **stack);


/*
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
*/
#endif
