/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:39:55 by preltien          #+#    #+#             */
/*   Updated: 2025/08/17 18:15:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Copies pointers from an old envp to a new one, skipping one entry. */
static void	copy_env_without_var(char **new_envp, char **old_envp,
		char **entry_to_skip)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_envp[i])
	{
		if (old_envp[i] != *entry_to_skip)
		{
			new_envp[j] = old_envp[i];
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
}

/* Removes a variable from the copied environment (for unset).
 * This involves creating a new, smaller envp array. */
int	unset_env_var(t_shell *state, const char *key)
{
	char	**entry_ptr;
	int		len;
	char	**new_envp;

	entry_ptr = find_env_var(state->envp, key);
	if (!entry_ptr)
		return (0);
	len = get_env_len(state->envp);
	new_envp = malloc(sizeof(char *) * len);
	if (!new_envp)
		return (1);
	copy_env_without_var(new_envp, state->envp, entry_ptr);
	free(*entry_ptr);
	free(state->envp);
	state->envp = new_envp;
	return (0);
}
