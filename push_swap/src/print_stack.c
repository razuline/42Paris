/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:36:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 12:24:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

void	print_stack(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->head)
	{
		ft_printf("Stack is empty!\n");
		return ;
	}
	current = stack->head;
	while (current)
	{
		ft_printf("%d ", current->value);
		current = current->next;
	}
	ft_printf("\n");
}
/*
int	main(void)
{
	t_stack	stack;

	stack.head = NULL;
	stack.size = 0;
	push_to(&stack, 5);
	push_to(&stack, 10);
	push_to(&stack, 15);
	ft_printf("Stack contents: \n");
	print_stack(&stack);

	return (0);
}
*/
