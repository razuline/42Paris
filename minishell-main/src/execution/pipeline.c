/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:47:21 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/24 13:01:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Launches all child processes in the pipeline without waiting for them.
 * It sets up the pipes between them. */
static void	launch_all_children(t_command *cmds, pid_t *pids, t_shell *state)
{
	t_exec_context	ctx;
	int				i;
	int				prev_fd;

	i = 0;
	prev_fd = -1;
	while (cmds)
	{
		setup_pipe_context(&ctx, cmds, state, prev_fd);
		pids[i] = fork_and_handle_child(&ctx);
		close_pipe_fds(&prev_fd, ctx.pipe_fd, ctx.is_last);
		if (!ctx.is_last)
			prev_fd = ctx.pipe_fd[0];
		cmds = cmds->next;
		i++;
	}
}

/* Waits for all child processes in the pipeline to complete.
 * The exit code of the last child is stored in the shell state. */
static void	wait_for_all_children(pid_t *pids, int num_cmds, t_shell *state)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		wait_for_child(pids[i], state);
		i++;
	}
}

/* Logic executed by a child process within a pipeline.
 * Sets up the standard input/output for the pipe and then runs the command. */
void	run_pipeline_child(t_exec_context *ctx)
{
	setup_input_output(ctx->prev_fd, ctx->pipe_fd, ctx->is_last);
	run_child_process(ctx->cmd, ctx->state);
}

/* Handles the execution of a series of commands linked by pipes. */
int	execute_pipeline(t_command *cmds, t_shell *state)
{
	pid_t	*pids;
	int		num_cmds;

	num_cmds = count_commands(cmds);
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
	{
		perror("minishell: malloc");
		return (1);
	}
	launch_all_children(cmds, pids, state);
	wait_for_all_children(pids, num_cmds, state);
	free(pids);
	return (state->exit_code);
}
