/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:51:10 by preltien          #+#    #+#             */
/*   Updated: 2025/09/09 20:56:04 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	write_heredoc_line(int fd, char *line, t_redir *redir, t_shell *state)
{
	char	*expanded;

	if (redir->expand)
		expanded = expand_str(line, state);
	else
		expanded = ft_strdup(line);
	if (!expanded)
		return (-1);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
	return (0);
}

int	handle_all_heredocs(t_redir *redir_list, t_shell *state)
{
	t_redir	*curr;

	curr = redir_list;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			g_signal_received = 0;
			if (read_single_heredoc(curr, state) < 0)
			{
				if (g_signal_received == SIGINT)
					return (-1);
				cleanup_heredocs(redir_list);
				return (-1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

static int	copy_heredoc_to_tmp(int fd_tmp, t_redir *redir)
{
	int		fd_heredoc;
	char	buf[1024];
	ssize_t	read_bytes;

	fd_heredoc = open(redir->tmp_name, O_RDONLY);
	if (fd_heredoc < 0)
	{
		perror("open heredoc");
		return (-1);
	}
	while (1)
	{
		read_bytes = read(fd_heredoc, buf, sizeof(buf));
		if (read_bytes <= 0)
			break ;
		write(fd_tmp, buf, read_bytes);
	}
	close(fd_heredoc);
	return (0);
}

int	apply_heredoc_redirections(t_redir *redir_list)
{
	t_redir	*curr;
	int		fd_tmp;
	char	tmp_name[32];

	ft_strcpy(tmp_name, "/tmp/heredoc_concatXXXXXX");
	fd_tmp = mkstemp(tmp_name);
	if (fd_tmp < 0)
		return (perror("mkstemp"), g_exit_status = 1, -1);
	curr = redir_list;
	while (curr)
	{
		if (curr->type == HEREDOC && curr->is_heredoc)
			copy_heredoc_to_tmp(fd_tmp, curr);
		curr = curr->next;
	}
	if (lseek(fd_tmp, 0, SEEK_SET) < 0 || dup2(fd_tmp, STDIN_FILENO) < 0)
		return (perror("dup2/lseek"), cleanup_tmp(fd_tmp, tmp_name));
	close(fd_tmp);
	unlink(tmp_name);
	return (0);
}

int	handle_heredocs_and_redirections(t_command *cmd, t_shell *state)
{
	printf(" [DEBUG] Handle heredoc appele\n");
	if (handle_all_heredocs(cmd->redir, state) < 0)
	{
		return (g_exit_status);
	}
	if (apply_heredoc_redirections(cmd->redir) < 0)
	{
		return (g_exit_status);
	}
	if (apply_redirections(cmd->redir) < 0)
	{
		return (g_exit_status);
	}
	return (0);
}
