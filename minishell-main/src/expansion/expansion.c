/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:25:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 18:19:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iterates through tokens and expands variables ($VAR, $?) for those
 * of type WORD that are not inside single quotes. */
int	expand_token(t_token *head, t_shell *state)
{
	t_token	*curr;
	char	*orig_value;
	char	*expanded_value;

	if (!head)
		return (0);
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == WORD && curr->quote_type != SINGLE_QUOTE)
		{
			orig_value = curr->value;
			expanded_value = expand_str(orig_value, state);
			if (!expanded_value)
				return (1);
			curr->value = expanded_value;
			free(orig_value);
		}
		curr = curr->next;
	}
	return (0);
}
