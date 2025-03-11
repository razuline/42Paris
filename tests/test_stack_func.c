/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:23:04 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/09 09:33:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <assert.h>
# include "../push_swap.h"

void	test_init_stack(void)
{
	t_stack	*stack;

	stack = init_stack();
	assert(stack != NULL);
	assert(stack->size == 0);
	assert(stack->head == NULL);
	assert(stack->tail == NULL);
	free_stack(stack);
}

void	test_push_pop(void)
{
	int		value;
	t_stack	*stack;

	stack = init_stack();
	push_to(stack, 10);
	assert(stack->size == 1);
	assert(stack->head->value == 10);

	push_to(stack, 20);
	assert(stack->size == 2);
	assert(stack->head->value == 20);
	assert(stack->head->next->value == 10);

	value = pop(stack);
	assert(value == 20);
	assert(stack->size == 1);
	assert(stack->head->value == 10);

	value = pop(stack);
	assert(value == 10);
	assert(stack->size == 0);

	free_stack(stack);
}

int	main(void)
{
	test_init_stack();
	test_push_pop();
	return (0);
}
