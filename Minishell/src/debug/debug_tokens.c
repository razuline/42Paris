/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:28:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/24 13:20:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Gets the string name of a token type enum. */
char	*get_type_name(int type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == APPEND_OUT)
		return ("APPEND_OUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	else
		return ("UNKNOWN");
}

/* (HELPER) Gets the string name of a quote type enum. */
char	*get_quote_name(int quote_type)
{
	if (quote_type == SINGLE_QUOTE)
		return ("SINGLE");
	if (quote_type == DOUBLE_QUOTE)
		return ("DOUBLE");
	return ("DEFAULT");
}

/* Prints a detailed list of tokens for debugging purposes. */
void	debug_print_tokens(t_token *head)
{
	t_token	*curr;
	int		i;

	curr = head;
	i = 0;
	printf("\n\033[1;34m--- TOKEN LIST ---\033[0m\n");
	if (!head)
	{
		printf(" (empty)\n");
		return ;
	}
	while (curr != NULL)
	{
		printf("Token %d: [TYPE: %-12s] [QUOTE: %-7s] [VALUE: \"%s\"]\n",
			i,
			get_type_name(curr->type),
			get_quote_name(curr->quote_type),
			curr->value);
		curr = curr->next;
		i++;
	}
	printf("\033[1;34m------------------\033[0m\n\n");
}
