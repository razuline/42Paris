/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:21:15 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 18:11:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* (First pass helper) Calculates the length of the Process ID ($$). */
static size_t	get_len_pid(void)
{
	char	*pid_str;
	size_t	len;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (0);
	len = ft_strlen(pid_str);
	free(pid_str);
	return (len);
}

/* (First pass helper) Calculates the length of an env variable's value. */
static size_t	get_len_var(const char *input, int *i_ptr, t_shell *state)
{
	char	*var_name;
	char	*value;
	size_t	len;

	var_name = get_var_name(input, i_ptr);
	if (!var_name)
		return (0);
	value = get_env_value(var_name, state->envp);
	free(var_name);
	if (!value)
		return (0);
	len = ft_strlen(value);
	free(value);
	return (len);
}

/* (First pass helper) Calculates the length of the exit status ($?). */
static size_t	get_len_exit_status(t_shell *state)
{
	char	*exit_code_str;
	size_t	len;

	exit_code_str = ft_itoa(state->exit_code);
	if (!exit_code_str)
		return (0);
	len = ft_strlen(exit_code_str);
	free(exit_code_str);
	return (len);
}

/* (First pass helper) Analyses a segment and updates the total length. */
static void	update_len_for_segment(const char *value, int *i, size_t *len,
		t_shell *state)
{
	if (value[*i] == '$' && value[*i + 1] != '\0')
	{
		(*i)++;
		if (value[*i] == '?')
		{
			(*i)++;
			*len += get_len_exit_status(state);
		}
		else if (value[*i] == '$')
		{
			(*i)++;
			*len += get_len_pid();
		}
		else if (ft_isalnum(value[*i]) || value[*i] == '_')
			*len += get_len_var(value, i, state);
		else
			(*len)++;
	}
	else
	{
		(*len)++;
		(*i)++;
	}
}

/* (First pass) Calculates the final length of the string after expansion.
 * This is done to allocate the exact amount of memory needed in one go. */
size_t	calculate_expanded_len(const char *value, t_shell *state)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (value[i])
	{
		update_len_for_segment(value, &i, &len, state);
	}
	return (len);
}
