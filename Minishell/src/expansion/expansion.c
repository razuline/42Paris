/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:25:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/10 18:52:57 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* (Second pass helper) Handles the expansion of the $? variable. */
static void	expand_exit_status(char *dest, size_t *j, t_shell *state)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(state->exit_code);
	*j = append_str_to_result(dest, exit_code_str, *j);
	free(exit_code_str);
}

/* (Second pass helper) Handles the expansion of a regular env variable. */
static void	expand_regular_var(const char *src, char *dest, t_indices *indices,
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

/* (Second pass) Analyses a segment (char, $VAR, $?) and appends the expanded
 * result to the destination string by calling the correct helper. */
static void	process_and_fill(const char *src, char *dest, t_indices *indices,
		t_shell *state)
{
	if (src[indices->i] == '$' && src[indices->i + 1])
	{
		(indices->i)++;
		if (src[indices->i] == '?')
		{
			(indices->i)++;
			expand_exit_status(dest, &indices->j, state);
		}
		else if (ft_isalnum(src[indices->i]) || src[indices->i] == '_')
			expand_regular_var(src, dest, indices, state);
		else
			dest[indices->j++] = '$';
	}
	else
		dest[indices->j++] = src[indices->i++];
}

/* Orchestrates the expansion of a string using a two-pass approach.
 * First pass calculates the final length, second pass fills the new string. */
char	*expand_str(const char *value, t_shell *state)
{
	char		*result;
	size_t		final_len;
	t_indices	indices;

	if (!value)
		return (NULL);
	final_len = calculate_expanded_len(value, state);
	result = malloc(sizeof(char) * (final_len + 1));
	if (!result)
		return (NULL);
	indices.i = 0;
	indices.j = 0;
	while (value[indices.i])
		process_and_fill(value, result, &indices, state);
	result[indices.j] = '\0';
	return (result);
}

/* Iterates through tokens and expands variables ($VAR, $?) for those
 * of type WORD that are not inside single quotes. */
int	expand_token(t_token *head, t_shell *state)
{
	t_token	*curr;
	char	*orig_value;
	char	*expanded_value;

	if (!head)
		return (0);
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == WORD && curr->quote_type != SINGLE_QUOTE)
		{
			orig_value = curr->value;
			expanded_value = expand_str(orig_value, state);
			if (!expanded_value)
			{
				return (1);
			}
			curr->value = expanded_value;
			free(orig_value);
		}
		curr = curr->next;
	}
	return (0);
}
