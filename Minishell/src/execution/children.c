/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:00:00 by preltien          #+#    #+#             */
/*   Updated: 2025/09/13 15:32:24 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_and_exit(int stdin_save, int stdout_save, int exit_code)
{
	restore_original_fds(stdin_save, stdout_save);
	exit(exit_code);
}

static void	handle_execve_error(int original_stdin, int original_stdout,
		char *last_command_name)
{
	int	exit_code;

	exit_code = 1;
	if (errno == ENOENT)
	{
		fprintf(stderr, "%s: command not found\n", last_command_name);
		exit_code = 127;
	}
	else if (errno == EACCES)
	{
		fprintf(stderr, "%s: command not found\n", last_command_name);
		exit_code = 126;
	}
	else
	{
		perror("execve");
		exit_code = 1;
	}
	restore_and_exit(original_stdin, original_stdout, exit_code);
}

int	has_heredoc(t_redir *redir_list)
{
	t_redir	*curr;

	curr = redir_list;
	while (curr)
	{
		if (curr->type == HEREDOC)
			return (1);
		curr = curr->next;
	}
	return (0);
}

static void	handle_pre_execution(t_command *cmd, t_shell *state,
		int original_stdin, int original_stdout)
{
	if (!cmd->argv || !cmd->argv[0])
		restore_and_exit(original_stdin, original_stdout, 0);
	get_absolute_path(cmd->argv, state);
	if (is_directory(cmd->argv[0]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		restore_and_exit(original_stdin, original_stdout, 126);
	}
}

void	run_child_process(t_command *cmd, t_shell *state)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = -1;
	original_stdout = -1;
	if (save_original_fds(&original_stdin, &original_stdout) != 0)
		exit(1);
	if (has_heredoc(cmd->redir))
	{
		if (handle_heredocs_and_redirections(cmd, state) < 0
			|| apply_redirections(cmd->redir) < 0)
			restore_and_exit(original_stdin, original_stdout, g_exit_status);
	}
	else if (apply_redirections(cmd->redir) < 0)
	{
		restore_and_exit(original_stdin, original_stdout, g_exit_status);
	}
	handle_pre_execution(cmd, state, original_stdin, original_stdout);
	if (is_builtin(cmd->argv[0]))
		restore_and_exit(original_stdin, original_stdout,
			execute_builtin(cmd->argv, state));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->argv[0], cmd->argv, state->envp);
	handle_execve_error(original_stdin, original_stdout, cmd->argv[0]);
}
