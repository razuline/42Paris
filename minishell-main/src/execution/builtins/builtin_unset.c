/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:58:48 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/19 15:34:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Built-in command: unset.
 * Deletes one or more variables from the environment. */
int	builtin_unset(char **argv, t_shell *state)
{
	int	i;
	int	ret_code;

	i = 1;
	ret_code = 0;
	while (argv[i])
	{
		if (!is_valid_varname(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret_code = 1;
		}
		else
			unset_env_var(state, argv[i]);
		i++;
	}
	return (ret_code);
}
