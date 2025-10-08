/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:19:24 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/12 19:34:37 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Allocates a new token and adds it to the end of the list.
 * This version takes ownership of the 'word' pointer and does not
 * duplicate it. The calling function should no longer free 'word'. */
t_token	*create_token(t_token_lst *lst, char *word, int type, int quote_info)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(word);
		return (NULL);
	}
	new_token->value = word;
	new_token->type = type;
	new_token->quote_type = quote_info;
	new_token->next = NULL;
	new_token->unclosed = 0;
	if (lst->head == NULL)
	{
		lst->head = new_token;
		lst->tail = new_token;
	}
	else
	{
		lst->tail->next = new_token;
		lst->tail = new_token;
	}
	return (new_token);
}

/* Prints a list of tokens (for debugging). */
void	print_tokens(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr != NULL)
	{
		printf("[TYPE: %s, VALUE: \"%s\"] -> \n", get_type_name(curr->type),
			curr->value);
		curr = curr->next;
	}
	printf("NULL\n");
}

/* Frees the memory of a token list. */
void	free_tokens(t_token *head)
{
	t_token	*curr;
	t_token	*next_node;

	curr = head;
	while (curr != NULL)
	{
		next_node = curr->next;
		free(curr->value);
		free(curr);
		curr = next_node;
	}
}
