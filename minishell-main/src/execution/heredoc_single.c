/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:51:10 by preltien          #+#    #+#             */
/*   Updated: 2025/09/09 17:10:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	init_heredoc_fd(t_redir *redir, int *fd, struct sigaction *sa_old)
{
	char	tmp_name[32];

	redir->tmp_name[0] = '\0';
	ft_strcpy(tmp_name, "/tmp/heredocXXXXXX");
	*fd = mkstemp(tmp_name);
	if (*fd < 0)
		return (perror("mkstemp failed"), g_exit_status = 1, -1);
	ft_strcpy(redir->tmp_name, tmp_name);
	sigaction(SIGINT, NULL, sa_old);
	return (0);
}

static int	check_heredoc_end(char *line, t_redir *redir)
{
	if (!line)
		return (1);
	if (g_exit_status == 130 || !ft_strcmp(line, redir->file))
		return (1);
	return (0);
}

static int	process_heredoc_line(int fd, char *line, t_redir *redir,
		t_shell *state)
{
	if (write_heredoc_line(fd, line, redir, state) < 0)
		return (-1);
	return (0);
}

static int	heredoc_loop(int fd, t_redir *redir, t_shell *state)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (check_heredoc_end(line, redir))
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(fd, line, redir, state) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	read_single_heredoc(t_redir *redir, t_shell *state)
{
	int					fd;
	struct sigaction	sa_old;
	int					ret;

	ret = 0;
	if (init_heredoc_fd(redir, &fd) < 0)
		return (-1);
	setup_heredoc_signals(&sa_old);
	if (heredoc_loop(fd, redir, state) < 0)
	{
		restore_signals(fd, &sa_old);
		g_exit_status = 1;
		return (-1);
	}
	restore_signals(fd, &sa_old);
	if (g_exit_status == 130)
		ret = -1;
	return (ret);
}
