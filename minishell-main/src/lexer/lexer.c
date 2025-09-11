/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:14:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 18:08:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to process one segment of the input line. */
static int	tokenize_segment(t_token_lst *lst, char **cursor)
{
	int	ret;

	ret = handle_double_op(lst, cursor);
	if (ret != 0)
		return (ret);
	ret = handle_single_op(lst, cursor);
	if (ret != 0)
		return (ret);
	return (handle_word(lst, cursor));
}

/* Iterates through the line and calls handlers for each segment. */
static int	lexer_loop(t_token_lst *lst, char *line)
{
	char	*cursor;
	int		ret;

	cursor = line;
	while (*cursor)
	{
		while (*cursor && ft_isspace(*cursor))
			cursor++;
		if (!*cursor)
			break ;
		ret = tokenize_segment(lst, &cursor);
		if (ret == -1)
		{
			ft_putstr_fd("minishell: malloc error during tokenization\n", 2);
			return (-1);
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
	if (lexer_loop(&lst, line) == -1)
	{
		free_tokens(lst.head);
		return (NULL);
	}
	return (lst.head);
}
