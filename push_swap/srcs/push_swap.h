/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:40:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/29 18:46:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
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
void	swap_a(t_stacks *stack_a);
void	swap_b(t_stacks *stack_b);

/* Check errors */
int		is_valid_number(char *str);
int		check_duplicates(int **array, int size);
long	ft_atol(const char *str);
void	check_errors(int ac, char **av);







#endif
