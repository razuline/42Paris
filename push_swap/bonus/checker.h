/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:11:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/10 18:13:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_stack
{
	int				value;
	struct s_stack	*next;
}				t_stack;

void	parse_args(t_stack **a, char **av);
void	swap(t_stack *stack);
void	push(t_stack **src, t_stack **dst);
void	rotate(t_stack **stack);
void	reverse_rotate(t_stack **stack);
int		is_sorted(t_stack *a);
int		is_empty(t_stack *stack);
void	free_stack(t_stack *stack);
void	if_error(void);
void	print_stack(t_stack *stack);
void	make_instructions(t_stack **a, t_stack **b);

#endif
