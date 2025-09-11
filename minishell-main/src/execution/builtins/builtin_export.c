/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:58:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 19:54:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints a standardised error message for invalid identifiers. */
static int	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

/* Handles an export argument that contains a value (e.g., "VAR=value"). */
static int	handle_export_with_value(t_shell *state, char *arg)
{
	char	*key;
	char	*value;
	int		ret;
	int		key_len;

	value = ft_strchr(arg, '=');
	key_len = value - arg;
	key = ft_substr(arg, 0, key_len);
	if (!key)
		return (1);
	value++;
	if (!is_valid_varname(key))
	{
		print_export_error(arg);
		free(key);
		return (1);
	}
	ret = set_env_var(state, key, value);
	free(key);
	return (ret);
}

/* Handles an export argument without a value (e.g., "VAR"). */
static int	handle_export_without_value(t_shell *state, char *arg)
{
	if (!is_valid_varname(arg))
		return (print_export_error(arg));
	if (!find_env_var(state->envp, arg))
		return (set_env_var(state, arg, NULL));
	return (0);
}

/* Built-in command: export.
 * Exports one or more variables to the environment.
 * If no arguments are given, it prints the environment in a sorted,
 * export-friendly format. */
int	builtin_export(char **argv, t_shell *state)
{
	int	i;
	int	ret_code;

	if (!argv[1])
	{
		print_env_sorted(state);
		return (0);
	}
	i = 1;
	ret_code = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			if (handle_export_with_value(state, argv[i]) != 0)
				ret_code = 1;
		}
		else
		{
			if (handle_export_without_value(state, argv[i]) != 0)
				ret_code = 1;
		}
		i++;
	}
	return (ret_code);
}
