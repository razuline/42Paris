/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:17:58 by preltien          #+#    #+#             */
/*   Updated: 2025/08/17 18:14:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper to create an environment entry string "KEY=VALUE".
 * If value is NULL, it creates a string with just "KEY". */
static char	*create_env_entry(const char *key, const char *value)
{
	char	*key_eq;
	char	*full_entry;

	if (!value)
		return (ft_strdup(key));
	key_eq = ft_strjoin(key, "=");
	if (!key_eq)
		return (NULL);
	full_entry = ft_strjoin(key_eq, value);
	free(key_eq);
	return (full_entry);
}

/* Adds or modifies a variable in the copied environment (for export).
 * If the variable exists, it is updated. If not, it is added.
 * This involves reallocating the entire envp array for new variables. */
int	set_env_var(t_shell *state, const char *key, const char *value)
{
	char	**entry_ptr;
	char	*new_entry;
	char	**new_envp;
	int		len;

	new_entry = create_env_entry(key, value);
	if (!new_entry)
		return (1);
	entry_ptr = find_env_var(state->envp, key);
	if (entry_ptr)
	{
		free(*entry_ptr);
		*entry_ptr = new_entry;
		return (0);
	}
	len = get_env_len(state->envp);
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
		return (free(new_entry), 1);
	ft_memcpy(new_envp, state->envp, sizeof(char *) * len);
	new_envp[len] = new_entry;
	new_envp[len + 1] = NULL;
	free(state->envp);
	state->envp = new_envp;
	return (0);
}
