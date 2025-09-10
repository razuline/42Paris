/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:33:07 by preltien          #+#    #+#             */
/*   Updated: 2025/09/10 13:30:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Interprets the exit status of a child process.
** Prints messages for signals like SIGQUIT. */
int	handle_child_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/* Executes a single command that is not part of a pipeline. */
static int	execute_single_command(t_command *cmd, t_shell *state)
{
	pid_t	pid;
	int		status;
	int		ret;

	if (cmd->argv && is_builtin(cmd->argv[0]))
		return (execute_builtin_with_redir(cmd, state));
	setup_non_interactive_signals();
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		run_child_process(cmd, state);
	waitpid(pid, &status, 0);
	ret = handle_child_status(status);
	g_exit_status = ret;
	cleanup_heredocs(cmd->redir);
	setup_interactive_signals();
	return (ret);
}

int	execute(t_command *cmds, t_shell *state)
{
	if (has_pipe(cmds))
		return (execute_pipeline(cmds, state));
	else
		return (execute_single_command(cmds, state));
}
