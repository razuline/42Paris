/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:00:00 by preltien          #+#    #+#             */
/*   Updated: 2025/09/09 19:52:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_and_exit(int stdin_save, int stdout_save, int exit_code)
{
	restore_original_fds(stdin_save, stdout_save);
	exit(exit_code);
}

static void	handle_execve_error(int original_stdin, int original_stdout)
{
	int	exit_code;

	exit_code = 1;
	if (errno == ENOENT)
		exit_code = 127;
	else if (errno == EACCES)
		exit_code = 126;
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
	if (is_builtin(cmd->argv[0]))
		restore_and_exit(original_stdin, original_stdout,
			execute_builtin(cmd->argv, state));
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
	if (handle_all_heredocs(cmd->redir, state) != 0
		|| apply_redirections(cmd->redir) != 0)
	{
		restore_and_exit(original_stdin, original_stdout, 1);
	}
	handle_pre_execution(cmd, state, original_stdin, original_stdout);
	setup_child_signals();
	execve(cmd->argv[0], cmd->argv, state->envp);
	handle_execve_error(original_stdin, original_stdout);
}
