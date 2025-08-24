/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:58:50 by preltien          #+#    #+#             */
/*   Updated: 2025/08/24 14:37:02 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Reads user input for the here-document and writes it to the pipe. */
static void	write_heredoc_line(int write_fd, char *line, t_shell *state,
		int expand)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_str(line, state);
		if (expanded)
			write(write_fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
}

void	read_heredoc_input(int write_fd, t_redir *redir, t_shell *state)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
			ft_putstr_fd("end-of-file (wanted `", 2);
			ft_putstr_fd(redir->file, 2);
			ft_putstr_fd("`)\n", 2);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(write_fd, line, state, redir->expand);
		free(line);
	}
}

/* Handles a here-document redirection (<<) using a pipe. */
int	handle_heredoc(t_redir *redir, t_shell *state)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	read_heredoc_input(pipefd[1], redir, state);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}
