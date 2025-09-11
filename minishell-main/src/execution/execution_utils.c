/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 20:31:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a given path corresponds to a directory. */
int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

/* Helper to save the standard file descriptors (stdin and stdout). */
int	save_original_fds(int *stdin_save, int *stdout_save)
{
	*stdin_save = dup(STDIN_FILENO);
	if (*stdin_save < 0)
	{
		perror("dup stdin failed");
		return (-1);
	}
	*stdout_save = dup(STDOUT_FILENO);
	if (*stdout_save < 0)
	{
		perror("dup stdout failed");
		close(*stdin_save);
		return (-1);
	}
	return (0);
}

/* Restores the standard file descriptors from a saved copy. */
int	restore_original_fds(int stdin_save, int stdout_save)
{
	if (stdin_save >= 0)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			perror("minishell: dup2 stdin");
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
