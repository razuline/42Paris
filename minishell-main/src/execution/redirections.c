/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:33 by preltien          #+#    #+#             */
/*   Updated: 2025/09/05 14:24:31 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles output redirections ('>' and '>>').
 * Opens the file with the correct flags (truncate or append). */
static int	redirect_output(const char *file, int type)
{
	int	fd;
	int	flags;

	if (type == APPEND_OUT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/* Handles input redirection ('<').
 * Opens the file for reading. */
static int	redirect_input(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/* Applies all redirections for a single command.
 * Iterates through the redirection list and handles each type. */
int	apply_redirections(t_redir *redir_list)
{
	while (redir_list)
	{
		if (redir_list->type == REDIRECT_IN)
		{
			if (redirect_input(redir_list->file) < 0)
				return (-1);
		}
		else if (redir_list->type == REDIRECT_OUT
			|| redir_list->type == APPEND_OUT)
		{
			if (redirect_output(redir_list->file, redir_list->type) < 0)
				return (-1);
		}
		redir_list = redir_list->next;
	}
	return (0);
}
