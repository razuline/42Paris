/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:51:14 by preltien          #+#    #+#             */
/*   Updated: 2025/09/10 13:38:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles the "-c" flag for non-interactive execution. */
static int	handle_non_interactive(char **argv, t_shell *state)
{
	parse_and_execute(state, argv[2]);
	ft_free_array(state->envp);
	return (state->exit_code);
}

/* Initialises the main shell structure (t_shell). */
void	init_shell_state(t_shell *state, char **envp)
{
	state->envp = create_env_copy(envp);
	if (!state->envp)
	{
		perror("minishell: malloc error during env copy");
		exit(EXIT_FAILURE);
	}
	state->exit_code = 0;
	state->should_exit = false;
	g_exit_status = 0;
}

/* Main entry point of the shell. */
int	main(int ac, char **av, char **envp)
{
	t_shell	shell_state;

	init_shell_state(&shell_state, envp);
	if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
		return (handle_non_interactive(av, &shell_state));
	(void)ac;
	(void)av;
	if (isatty(STDIN_FILENO))
		display_title();
	setup_interactive_signals();
	prompt_loop(&shell_state);
	ft_free_array(shell_state.envp);
	rl_clear_history();
	return (g_exit_status);
}
