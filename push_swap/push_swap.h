/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:17:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/07 19:08:42 by erazumov         ###   ########.fr       */
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

/* Stack's operations */
t_stack	*init_stack(void);
void	free_stack(t_stack *stack);
void	push_to(t_stack *stack, int value);
int		pop(t_stack *stack);
void	parse_input(t_stack *stack, char **av);

/* Operations */
void	swap(t_stack *stack);
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);

/* Utils */
void	if_error(const char *str);

#endif
