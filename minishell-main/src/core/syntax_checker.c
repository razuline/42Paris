/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:01:48 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/11 18:55:49 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a line has unclosed single or double quotes.
** Returns 1 if there is an unclosed quote, 0 otherwise.
** A state machine tracks whether the parser is currently inside a quote. */
int	has_unclosed_quotes(char *line)
{
	char	quote_char;
	int		i;

	quote_char = 0;
	i = 0;
	while (line[i])
	{
		if (quote_char == 0 && (line[i] == '\'' || line[i] == '"'))
			quote_char = line[i];
		else if (quote_char != 0 && line[i] == quote_char)
			quote_char = 0;
		i++;
	}
	if (quote_char != 0)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (1);
	}
	return (0);
}
