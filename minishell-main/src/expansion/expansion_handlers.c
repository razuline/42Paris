/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:15:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 20:26:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* (Second pass helper) Handles the expansion of the $? variable. */
void	expand_exit_status(char *dest, size_t *j, t_shell *state)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(state->exit_code);
	*j = append_str_to_result(dest, exit_code_str, *j);
	free(exit_code_str);
}

/* (Second pass helper) Handles the expansion of the $$ variable. */
void	expand_pid(char *dest, size_t *j)
{
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return ;
	*j = append_str_to_result(dest, pid_str, *j);
	free(pid_str);
}

/* (Second pass helper) Handles the expansion of a regular env variable. */
void	expand_regular_var(const char *src, char *dest, t_indices *indices,
		t_shell *state)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(src, &indices->i);
	var_value = get_env_value(var_name, state->envp);
	indices->j = append_str_to_result(dest, var_value, indices->j);
	free(var_name);
	free(var_value);
}
