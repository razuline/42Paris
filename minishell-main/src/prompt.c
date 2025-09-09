/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:39:38 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 20:08:29 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a string consists only of whitespace characters. */
static int	is_whitespace(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

/* Handles the logic for a valid, non-empty line of input. */
static void	handle_valid_line(char *line, t_shell *state)
{
	if (has_unclosed_quotes(line))
	{
		state->exit_code = 2;
		g_exit_status = 2;
		return ;
	}
	if (isatty(STDIN_FILENO))
		add_history(line);
	parse_and_execute(state, line);
}

/* Reads and processes a single line from the user. */
static void	process_line(t_shell *state)
{
	char	*line;

	state->exit_code = g_exit_status;
	g_signal_received = 0;
	line = read_line_input();
	if (g_signal_received == SIGINT)
		state->exit_code = 130;
	if (line == NULL)
	{
		state->should_exit = true;
		printf("exit\n");
		return ;
	}
	if (line[0] != '\0' && !is_whitespace(line))
		handle_valid_line(line, state);
	else
		g_exit_status = state->exit_code;
	free(line);
}

/* Orchestrates the parsing and execution of a command line. */
void	parse_and_execute(t_shell *state, char *line)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = lexer(line);
	commands = NULL;
	if (tokens && expand_token(tokens, state) == 0)
		commands = parser(tokens, state);
	if (commands != NULL)
	{
		if (commands->argv && commands->argv[0]
			&& ft_strcmp(commands->argv[0], "exit") == 0)
			execute_builtin(commands->argv, state);
		else
			state->exit_code = execute(commands, state);
	}
	g_exit_status = state->exit_code;
	if (tokens)
		free_tokens(tokens);
	if (commands)
		free_commands(commands);
}

/* The main interactive loop of the shell. */
void	prompt_loop(t_shell *state)
{
	while (state->should_exit == false)
	{
		process_line(state);
	}
}
