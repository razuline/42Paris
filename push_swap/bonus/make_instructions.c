/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:40:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/10 18:13:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"

void	make_instructions(t_stack **a, t_stack **b)
{
	char	*line;

	while ((line = get_next_line(0)))
	{
		if (line[0] == '\0')
			break ;
		if (ft_strcmp(line, "sa\n") == 0)
			swap(*a);
		else if (ft_strcmp(line, "sb\n") == 0)
			swap(*b);
		else if (ft_strcmp(line, "pa\n") == 0)
			push(b, a);
		else if (ft_strcmp(line, "pb\n") == 0)
			push(a, b);
		else if (ft_strcmp(line, "ra\n") == 0)
			rotate(a);
		else if (ft_strcmp(line, "rb\n") == 0)
			rotate(b);
		else if (ft_strcmp(line, "rra\n") == 0)
			reverse_rotate(a);
		else if (ft_strcmp(line, "rrb\n") == 0)
			reverse_rotate(b);
		else
		{
			error();
			free(line);
			return ;
		}

		free(line);
	}
}
