/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:17:58 by preltien          #+#    #+#             */
/*   Updated: 2025/09/10 19:58:01 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper to create an environment entry string "KEY=VALUE".
 * If value is NULL, it creates a string with just "KEY". */
static char	*create_env_entry(const char *key, const char *value)
{
	char	*key_eq;
	char	*full_entry;

	key_eq = ft_strjoin(key, "=");
	if (!key_eq)
		return (NULL);
	if (value)
		full_entry = ft_strjoin(key_eq, value);
	else
		full_entry = ft_strdup(key_eq);
	free(key_eq);
	return (full_entry);
}

static int	replace_env_var(char **entry_ptr, char *new_entry)
{
	if (!entry_ptr || !new_entry)
		return (1);
	free(*entry_ptr);
	*entry_ptr = new_entry;
	return (0);
}

static int	copy_old_envp(char **old_envp, char **new_envp, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	free_old_envp(char **envp, int len)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (i < len)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
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

	if (!state || !key)
		return (1);
	new_entry = create_env_entry(key, value);
	if (!new_entry)
		return (1);
	entry_ptr = find_env_var(state->envp, key);
	if (entry_ptr)
		return (replace_env_var(entry_ptr, new_entry));
	len = get_env_len(state->envp);
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
		return (free(new_entry), 1);
	if (copy_old_envp(state->envp, new_envp, len))
		return (free(new_entry), 1);
	new_envp[len] = new_entry;
	new_envp[len + 1] = NULL;
	free_old_envp(state->envp, len);
	state->envp = new_envp;
	return (0);
}
