/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:58:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 17:07:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Built-in command: exit.
 * Frees all major shell resources and terminates the program. */
int	builtin_exit(char **argv, t_shell *state)
{
	long long	exit_code_ll;

	ft_putstr_fd("exit\n", 1);
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!argv[1])
		exit_code_ll = state->exit_code;
	else if (!ft_atoll_check(argv[1], &exit_code_ll))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code_ll = 2;
	}
	state->exit_code = (int)(exit_code_ll % 256);
	state->should_exit = true;
	return (state->exit_code);
}
