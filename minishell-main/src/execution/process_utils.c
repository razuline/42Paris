/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:04:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/24 17:10:09 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Forks the current process and executes the child's logic. */
int	fork_and_handle_child(t_exec_context *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
		run_pipeline_child(ctx);
	return (pid);
}

/* Waits for a specific child process to terminate and updates the exit code. */
void	wait_for_child(pid_t pid, t_shell *state)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		state->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		state->exit_code = 128 + WTERMSIG(status);
	}
}
