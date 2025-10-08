/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:51:10 by preltien          #+#    #+#             */
/*   Updated: 2025/09/05 15:14:27 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
}

void	cleanup_heredocs(t_redir *redir_list)
{
	t_redir	*curr;

	curr = redir_list;
	while (curr)
	{
		if (curr->type == HEREDOC && curr->is_heredoc)
		{
			if (curr->tmp_name[0])
			{
				unlink(curr->tmp_name);
				curr->tmp_name[0] = '\0';
			}
		}
		curr = curr->next;
	}
}

int	cleanup_tmp(int fd, char *name)
{
	close(fd);
	unlink(name);
	g_exit_status = 1;
	return (-1);
}
