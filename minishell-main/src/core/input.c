/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:23:17 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/19 20:20:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Reads a line of input in interactive mode using readline. */
static char	*read_interactive_line(void)
{
	char	*prompt;
	char	*line;

	prompt = build_prompt();
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	return (line);
}

/* Reads a line of input in non-interactive mode using get_next_line(). */
static char	*read_non_interactive_line(void)
{
	char	*line;
	size_t	len;

	line = get_next_line(STDIN_FILENO);
	if (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	return (line);
}

/* Reads a line of input, choosing the correct method based on
 * whether the shell is running interactively or not. */
char	*read_line_input(void)
{
	if (isatty(STDIN_FILENO))
		return (read_interactive_line());
	else
		return (read_non_interactive_line());
}
