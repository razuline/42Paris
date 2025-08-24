/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:14:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/18 11:03:08 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iterates through the line and calls handlers for each segment. */
static void	lexer_loop(t_token_lst *lst, char *line)
{
	char	*cursor;

	cursor = line;
	while (*cursor)
	{
		while (*cursor && ft_isspace(*cursor))
			cursor++;
		if (!*cursor)
			break ;
		if (handle_double_op(lst, &cursor) == 1)
			;
		else if (handle_single_op(lst, &cursor) == 1)
			;
		else
			handle_word(lst, &cursor);
	}
}

/* Converts the raw command line into a list of tokens. */
t_token	*lexer(char *line)
{
	t_token_lst	lst;

	if (!line)
		return (NULL);
	lst.head = NULL;
	lst.tail = NULL;
	lexer_loop(&lst, line);
	return (lst.head);
}
