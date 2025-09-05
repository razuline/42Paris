/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:39:55 by preltien          #+#    #+#             */
/*   Updated: 2025/09/04 18:10:39 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Counts the number of strings in an environment array. */
int	get_env_len(char **envp)
{
	int	len;

	len = 0;
	while (envp && envp[len])
		len++;
	return (len);
}

/* Creates a deep, allocated copy of the environment (envp). */
char	**create_env_copy(char **envp)
{
	char	**new_envp;
	int		len;
	int		i;

	len = get_env_len(envp);
	new_envp = malloc(sizeof(char *) * (len + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

/* Finds an environment variable by its key. */
char	**find_env_var(char **envp, const char *key)
{
	int		i;
	size_t	key_len;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

/* Finds an environment variable by its key and returns a copy of its value. */
char	*get_env_value(const char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (ft_strdup(""));
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return (ft_strdup(envp[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}
