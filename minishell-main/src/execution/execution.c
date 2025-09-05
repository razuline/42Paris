/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:33:07 by preltien          #+#    #+#             */
/*   Updated: 2025/09/05 17:01:14 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	execute_single_command(t_command *cmd, t_shell *state)
{
	pid_t	pid;
	int		status;

	if (cmd->argv && is_builtin(cmd->argv[0]))
	{
		return (execute_builtin(cmd->argv, state));
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		run_child_process(cmd, state);
	waitpid(pid, &status, 0);
	cleanup_heredocs(cmd->redir);
	return (handle_child_status(status));
}

int	execute(t_command *cmds, t_shell *state)
{
	if (has_pipe(cmds))
		return (execute_pipeline(cmds, state));
	else
		return (execute_single_command(cmds, state));
}
