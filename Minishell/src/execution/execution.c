/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:33:07 by preltien          #+#    #+#             */
/*   Updated: 2025/08/24 14:03:39 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles fork(), waitpid(), and signal setup for a single external command */
static int	exec_cmd(t_command *cmd, t_shell *state)
{
	pid_t	pid;
	int		status;

	setup_non_interactive_signals();
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		run_child_process(cmd, state);
	}
	waitpid(pid, &status, 0);
	setup_interactive_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/* Prepares and executes an external command in a new process */
static int	execute_external_command(t_command *cmd, t_shell *state)
{
	get_absolute_path(cmd->argv, state);
	return (exec_cmd(cmd, state));
}

/* Executes a single command (not part of a pipeline) */
static int	execute_single_command(t_command *cmd, t_shell *state)
{
	int	exit_code;
	int	original_stdin;
	int	original_stdout;

	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (execute_builtin(cmd->argv, state));
	if (is_builtin(cmd->argv[0]))
	{
		if (save_original_fds(&original_stdin, &original_stdout) != 0)
			return (1);
		if (apply_redirections(cmd->redir, state) < 0)
			exit_code = 1;
		else
			exit_code = execute_builtin(cmd->argv, state);
		restore_original_fds(original_stdin, original_stdout);
		return (exit_code);
	}
	return (execute_external_command(cmd, state));
}

/* Entry point for execution: dispatches to single command or pipeline */
int	execute(t_command *cmds, t_shell *state)
{
	if (has_pipe(cmds))
		return (execute_pipeline(cmds, state));
	else
		return (execute_single_command(cmds, state));
}

/* Logic executed by the child process.
 * Applies redirections, handles built-ins within pipes, finds the path,
 * and calls execve. Exits with an appropriate status code on failure. */
void	run_child_process(t_command *cmd, t_shell *state)
{
	if (apply_redirections(cmd->redir, state) < 0)
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd->argv, state));
	get_absolute_path(cmd->argv, state);
	if (is_directory(cmd->argv[0]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	execve(cmd->argv[0], cmd->argv, state->envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES)
		exit(126);
	exit(1);
}
