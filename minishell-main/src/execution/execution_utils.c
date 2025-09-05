/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/05 14:24:12 by preltien         ###   ########.fr       */
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
	if (*stdin_save < 0)
	{
		perror("dup stdin failed");
		*stdin_save = -1;
	}
	*stdout_save = dup(STDOUT_FILENO);
	if (*stdout_save < 0)
	{
		perror("dup stdout failed");
		if (*stdin_save >= 0)
			close(*stdin_save);
		*stdout_save = -1;
	}
	if (*stdin_save < 0 && *stdout_save < 0)
		return (-1);
	else
		return (0);
}

int	restore_original_fds(int stdin_save, int stdout_save)
{
	if (stdin_save >= 0)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			perror("minishell: dup2 stdin");
		else
			close(stdin_save);
	}
	if (stdout_save >= 0)
	{
		if (dup2(stdout_save, STDOUT_FILENO) == -1)
			perror("minishell: dup2 stdout");
		close(stdout_save);
	}
	return (0);
}
