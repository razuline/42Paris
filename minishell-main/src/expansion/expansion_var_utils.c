/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:19:48 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/18 10:46:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a character is a valid character for a variable name
 * (alphanumeric or underscore). */
static int	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* Extracts a valid variable name from an input string starting at a
 * given position (e.g., extracts "USER" from "$USER_PATH"). */
char	*get_var_name(const char *input, int *i_ptr)
{
	int		len;
	int		start_pos;
	char	*var_name;

	len = 0;
	start_pos = *i_ptr;
	while (input[start_pos + len] && is_valid_char(input[start_pos + len]))
		len++;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(input, start_pos, len);
	*i_ptr += len;
	return (var_name);
}

/* Checks if an entire string is a valid shell identifier.
 * An identifier must start with a letter or underscore, and may then
 * contain letters, numbers, or underscores. */
int	is_valid_varname(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!is_valid_char(name[i]))
			return (0);
		i++;
	}
	return (1);
}
