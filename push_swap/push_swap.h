/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:17:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/07 15:17:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct	s_elem
{
	int				number;
	int				index;
	struct s_elem	*prev;
	struct s_elem	*next;
}				t_elem;

/* Operations */
void	sa(t_elem **stack, int a);
void	sb(t_elem **stack, int a);
void	pa(t_elem **stack_a, t_elem **stack_b);
void	pb(t_elem **stack_a, t_elem **stack_b);


#endif
