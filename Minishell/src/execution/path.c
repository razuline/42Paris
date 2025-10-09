/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:28:17 by preltien          #+#    #+#             */
/*   Updated: 2025/09/02 16:02:06 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a command string already contains a path (i.e., a '/'). */
static int	is_path(const char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

/* Retrieves the value of the PATH environment variable. */
static char	*get_path_from_env(t_shell *state)
{
	int	i;

	i = 0;
	while (state->envp && state->envp[i])
	{
		if (ft_strncmp(state->envp[i], "PATH=", 5) == 0)
			return (ft_strdup(state->envp[i] + 5));
		i++;
	}
	return (NULL);
}

/* Searches for an executable file in the directories listed in paths. */
static char	*find_exec_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*tmp_path;
	char	*full_path;

	i = 0;
	while (paths && paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		if (!tmp_path)
			return (NULL);
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/* Finds the absolute path of a command and updates argv[0].
 * If the command does not contain a '/', it searches the PATH environment
 * variable. */
void	get_absolute_path(char **argv, t_shell *state)
{
	char	*path_env;
	char	**paths;
	char	*exec_path;

	if (!argv || !argv[0] || !argv[0][0])
		return ;
	if (is_path(argv[0]))
		return ;
	path_env = get_path_from_env(state);
	if (!path_env)
		return ;
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return ;
	exec_path = find_exec_in_paths(argv[0], paths);
	if (paths)
		ft_free_array(paths);
	if (exec_path)
	{
		free(argv[0]);
		argv[0] = exec_path;
	}
}
