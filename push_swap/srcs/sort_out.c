/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:36:24 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/23 13:46:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

int	sort_nbr(char *str, t_stack **stack)
{
	int		error;
	int		nbr;

	error = 0;
	if (!check_digit(str) || ft_strlen(str) > 11)
		return (free_if_error(&stack), ft_printf("Error!\n"), NULL);
	nbr = safe_atoi(str, &error);
	if (error)
		return (free_if_error(&stack), ft_printf("Error!\n"), NULL);
	add_node(&stack, nbr);
	return (0);
}

int	sort_arg(char *arg, t_stack **stack)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(arg[i], ' ');
		if (!split)
			return (-1);
	while (split[i])
	{
		if (sort_nbr(split[i], stack) == -1)
			return (free(split[i]), free(split), -1);
		free(split[i]);
		i++;
	}
	free (split);
	return (0);
}

t_stack	*sort_input(int ac, char **av)
{
	t_stack	*stack;
	int		i;

	stack = NULL;
	i = 1;
	while (i < ac)
	{
		if (sort_arg(av[i], &stack) == -1)
			return (NULL);
		i++;
	}
	if (check_dup(stack))
		(free_if_error(&stack), ft_printf("Error!\n"), NULL);
	return (stack);
}

/* TESTING
static void	print_stack(t_stack *stack)
{
	while (stack)
	{
		ft_printf("%d\n", stack->item);
		stack = stack->next;
	}
}

int main(int argc, char **argv)
{
	t_stack	*stack;

	if (argc < 2)
	{
		ft_printf("Usage: ./push_swap <numbers>\n");
		return (1);
	}
	stack = sort_input(argc, argv);
	if (!stack)
		return (1);

	print_stack(stack);

	free_if_error(&stack);
	return (0);
}
*/
