/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:13:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 18:14:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
