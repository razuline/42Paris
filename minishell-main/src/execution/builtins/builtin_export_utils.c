/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:07:39 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/18 10:26:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* A simple bubble sort for an array of strings. */
static void	bubble_sort_array(char **array, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Prints the environment in the format "export KEY="VALUE"".
 * This is used when 'export' is called with no arguments. */
void	print_env_sorted(t_shell *state)
{
	char	**env_copy;
	int		len;
	int		i;
	char	*eq_pos;

	len = get_env_len(state->envp);
	env_copy = create_env_copy(state->envp);
	if (!env_copy)
		return ;
	bubble_sort_array(env_copy, len);
	i = 0;
	while (env_copy[i])
	{
		eq_pos = ft_strchr(env_copy[i], '=');
		if (eq_pos)
			printf("export %.*s=\"%s\"\n", (int)(eq_pos - env_copy[i]),
				env_copy[i], eq_pos + 1);
		else
			printf("export %s\n", env_copy[i]);
		i++;
	}
	ft_free_array(env_copy);
}
