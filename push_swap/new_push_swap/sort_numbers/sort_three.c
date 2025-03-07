/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/07 12:59:29 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

int	check_case(t_node *stack)
{
	if ((stack->number < stack->next->number)
		&& (stack->next->number < stack->prev->number))
		return (1);
	
}
