#define _POSIX_C_SOURCE 200809L
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:51:10 by preltien          #+#    #+#             */
/*   Updated: 2025/09/09 20:40:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* (HELPER) Initializes the temporary file for the heredoc. */
static int	init_heredoc_fd(t_redir *redir, int *fd)
{
	char	tmp_name[32];

	ft_strcpy(tmp_name, "/tmp/heredocXXXXXX");
	*fd = mkstemp(tmp_name);
	if (*fd < 0)
	{
		perror("minishell: mkstemp");
		return (-1);
	}
	ft_strcpy(redir->tmp_name, tmp_name);
	return (0);
}

/* (HELPER) Configures a temporary signal handler for SIGINT (Ctrl-C). */
static void	setup_heredoc_signals(struct sigaction *sa_old)
{
	struct sigaction	sa_new;

	sa_new.sa_handler = heredoc_sigint;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, sa_old);
	rl_catch_signals = 0;
}

/* (HELPER) Restores the original signal handler for SIGINT. */
static void	restore_signals(int fd, struct sigaction *sa_old)
{
	close(fd);
	sigaction(SIGINT, sa_old, NULL);
	rl_catch_signals = 1;
}

/* The main loop for reading heredoc input line by line. */
static int	heredoc_loop(int fd, t_redir *redir, t_shell *state)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_signal_received == SIGINT
			|| ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		if (write_heredoc_line(fd, line, redir, state) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

/* Manages the process of reading a single heredoc. */
int	read_single_heredoc(t_redir *redir, t_shell *state)
{
	int					fd;
	struct sigaction	sa_old;

	if (init_heredoc_fd(redir, &fd) < 0)
		return (-1); // Return -1 only on a true error
	setup_heredoc_signals(&sa_old);
	heredoc_loop(fd, redir, state);
	restore_signals(fd, &sa_old);
	if (g_signal_received == SIGINT)
	{
		g_exit_status = 130;
		unlink(redir->tmp_name);
	}
	return (0);
}
