/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:30:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/23 13:43:04 by erazumov         ###   ########.fr       */
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

/* Utility functions */
int	if_sorted(t_stack *stack);
int	safe_atoi(char *str, int *error);

#endif
