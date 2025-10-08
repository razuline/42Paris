/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:14:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/12 19:31:42 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iterates through the line and calls handlers for each segment. */
static int	lexer_loop(t_token_lst *lst, char *line)
{
	char	*cursor;
	int		result;

	cursor = line;
	while (*cursor)
	{
		while (*cursor && ft_isspace(*cursor))
			cursor++;
		if (!*cursor)
			break ;
		if (handle_double_op(lst, &cursor) == 1)
			continue ;
		else if (handle_single_op(lst, &cursor) == 1)
			continue ;
		else
		{
			result = handle_word(lst, &cursor);
			if (result != 0)
				return (1);
		}
	}
	return (0);
}

/* Converts the raw command line into a list of tokens. */
t_token	*lexer(char *line)
{
	t_token_lst	lst;

	if (!line)
		return (NULL);
	lst.head = NULL;
	lst.tail = NULL;
	if (lexer_loop(&lst, line) != 0)
	{
		free_tokens(lst.head);
		return (NULL);
	}
	return (lst.head);
}

int	check_unclosed_quotes_in_word(const char *start, int len, int *quote_type)
{
	int	in_s_quote;
	int	in_d_quote;
	int	i;

	in_s_quote = 0;
	in_d_quote = 0;
	i = 0;
	while (i < len)
	{
		if (start[i] == '\'' && !in_d_quote)
			in_s_quote = !in_s_quote;
		else if (start[i] == '"' && !in_s_quote)
			in_d_quote = !in_d_quote;
		i++;
	}
	if (in_s_quote)
		*quote_type = 1;
	else if (in_d_quote)
		*quote_type = 2;
	else
		*quote_type = 0;
	return (in_s_quote || in_d_quote);
}
