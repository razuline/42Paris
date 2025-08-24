/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/17 18:07:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a command name corresponds to a built-in command. */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/* Checks if a given path corresponds to a directory. */
int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

/* Dispatches to the correct built-in function and returns its exit code. */
int	execute_builtin(char **argv, t_shell *state)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, state));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(state));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, state));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, state));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv, state));
	return (1);
}

/* Helper to save the standard file descriptors (stdin and stdout). */
int	save_original_fds(int *stdin_save, int *stdout_save)
{
	*stdin_save = dup(STDIN_FILENO);
	if (*stdin_save == -1)
	{
		perror("minishell: dup");
		return (-1);
	}
	*stdout_save = dup(STDOUT_FILENO);
	if (*stdout_save == -1)
	{
		close(*stdin_save);
		perror("minishell: dup");
		return (-1);
	}
	return (0);
}

/* Helper to restore the saved standard file descriptors. */
int	restore_original_fds(int stdin_save, int stdout_save)
{
	if (dup2(stdin_save, STDIN_FILENO) == -1
		|| dup2(stdout_save, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(stdin_save);
		close(stdout_save);
		return (-1);
	}
	close(stdin_save);
	close(stdout_save);
	return (0);
}
