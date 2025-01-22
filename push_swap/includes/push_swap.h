/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:23:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/22 13:41:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <ctype.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct	s_stacks
{
	int	*arr; /* To store elements of the stack */
	int	size; /* Current size of the stack */

}	t_stacks;

/* Stack Operations */
void	swap_a(t_stacks *stack);
void	swap_b(t_stacks *stack);






#endif
