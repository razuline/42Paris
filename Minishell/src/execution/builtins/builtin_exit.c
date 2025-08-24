/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:58:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/19 20:54:55 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Built-in command: exit.
 * Frees all major shell resources and terminates the program. */
int	builtin_exit(char **argv, t_shell *state)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 2);
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!argv[1])
		exit_code = state->exit_code;
	else if (!ft_str_is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit_code = 255;
	}
	else
		exit_code = ft_atoi(argv[1]);
	state->exit_code = exit_code % 256;
	state->should_exit = true;
	return (state->exit_code);
}
