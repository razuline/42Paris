/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:56:12 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/17 18:10:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prepares the execution context for a command in the pipeline. */
void	setup_pipe_context(t_exec_context *ctx, t_command *cmd, t_shell *state,
		int prev_fd)
{
	ctx->cmd = cmd;
	ctx->state = state;
	ctx->prev_fd = prev_fd;
	ctx->is_last = (cmd->next == NULL);
	if (create_pipe_if_needed(ctx->pipe_fd, ctx->is_last) != 0)
		exit(EXIT_FAILURE);
}

/* Closes the necessary pipe file descriptors in the parent process
 * after each fork. */
void	close_pipe_fds(int *prev_fd, int pipe_fd[2], int is_last)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!is_last)
		close(pipe_fd[1]);
}

/* Creates a new pipe, unless the command is the last in the pipeline. */
int	create_pipe_if_needed(int pipe_fd[2], int is_last)
{
	if (!is_last)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("minishell: pipe");
			return (1);
		}
	}
	return (0);
}

/* Sets up the standard input and output for a process in a pipeline
 * using dup2. */
void	setup_input_output(int prev_fd, int pipe_fd[2], int is_last)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (!is_last)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
}
