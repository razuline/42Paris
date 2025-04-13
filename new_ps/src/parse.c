/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:58:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 13:27:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static bool	check_dup(t_stack *stack, int num);
static bool	validate_add_node(char *num_str, t_stack *stack_a);
static void	process_single_str_arg(char *arg_str, t_stack *stack_a);
static void	process_mult_args(int ac, char **av, t_stack *stack_a);

void	parse_fill_stack(int ac, char **av, t_stack *stack_a)
{
	if (ac == 2)
		process_single_str_arg(av[1], stack_a);
	else
		process_mult_args(ac, av, stack_a);
}

static bool	check_dup(t_stack *stack, int num)
{
	t_node	*current;

	if (!stack)
		return (false);
	current = stack->head;
	while (current)
	{
		if (current->value == num)
			return (true);
		current = current->next;
	}
	return (false);
}

static bool	validate_add_node(char *num_str, t_stack *stack_a)
{
	long	num_long;
	int		num_int;
	t_node	*new_node;

	if (!is_num(num_str))
		return (false);

	num_long = ft_atol(num_str);
	if (num_long > INT_MAX || num_long < INT_MIN)
		return (false);
	num_int = (int)num_long;
	if (check_dup(stack_a, num_int))
		return (false);
	new_node = create_node(num_int);
	if (!new_node)
		return (false);
	add_node_back(stack_a, new_node);
	return (true);
}

static void	process_single_str_arg(char *arg_str, t_stack *stack_a)
{
	int		i;
	char	**nums;
	bool	success;

	nums = ft_split(arg_str, ' ');
	if (!nums)
		error_exit(stack_a, NULL);
	if (!nums[0])
	{
		free_split_result(nums);
		error_exit(stack_a, NULL);
	}
	i = 0;
	while (nums[i])
	{
		success = validate_add_node(nums[i], stack_a);
		if (!success)
		{
			free_split_result(nums);
			error_exit(stack_a, NULL);
		}
		i++;
	}
	free_split_result(nums);
}

static void	process_mult_args(int ac, char **av, t_stack *stack_a)
{
	int		i;
	bool	success;

	i = 1;
	while (i < ac)
	{
		success = validate_add_node(av[i], stack_a);
		if (!success)
			error_exit(stack_a, NULL);
		i++;
	}
}
