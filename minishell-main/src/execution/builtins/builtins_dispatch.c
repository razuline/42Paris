/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:29:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/10 13:30:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a command name corresponds to a built-in command. */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/* Dispatches to the correct built-in function and returns its exit code. */
int	execute_builtin(char **argv, t_shell *state)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, state));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(state));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, state));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, state));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv, state));
	return (1);
}

/* Handles the execution of a built-in command with its redirections. */
int	execute_builtin_with_redir(t_command *cmd, t_shell *state)
{
	int original_stdin;
	int original_stdout;
	int exit_code;

	original_stdin = -1;
	original_stdout = -1;
	if (save_original_fds(&original_stdin, &original_stdout) != 0)
		return (1);
	if (apply_redirections(cmd->redir) != 0)
	{
		restore_original_fds(original_stdin, original_stdout);
		return (1);
	}
	exit_code = execute_builtin(cmd->argv, state);
	restore_original_fds(original_stdin, original_stdout);
	return (exit_code);
}
