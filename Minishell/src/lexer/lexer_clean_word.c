/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clean_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:38:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/11 22:02:19 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles quote characters (' and ") while parsing a word.
 * It updates the quote state (open/closed) and advances the 'i' index
 * to skip the quote character. */
static int	handle_quotes(const char *str, t_clean_state *s)
{
	if (str[s->i] == '\'' && !s->in_d_quote)
	{
		s->in_s_quote = !s->in_s_quote;
		s->i++;
		return (1);
	}
	if (str[s->i] == '"' && !s->in_s_quote)
	{
		s->in_d_quote = !s->in_d_quote;
		s->i++;
		return (1);
	}
	return (0);
}

/* Handles backslash escape sequences ('\').
 * If a backslash is found (outside of single quotes), it copies the
 * next character and advances the iterators appropriately. */
static int	handle_escape(char *dest, const char *str, t_clean_state *s,
		int len)
{
	char	next_char;

	if (str[s->i] == '\\' && s->in_d_quote && s->i + 1 < len)
	{
		next_char = str[s->i + 1];
		if (next_char == '$' || next_char == '"' || next_char == '\\')
		{
			dest[s->j++] = str[s->i + 1];
			s->i += 2;
			return (1);
		}
	}
	return (0);
}

/* Allocates and cleans a word by removing outer quotes and
 * interpreting escape sequences. This function orchestrates calls
 * to helper functions for each character. */
char	*extract_and_clean_word(const char *start, int len)
{
	char			*dest;
	t_clean_state	s;

	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	s.i = 0;
	s.j = 0;
	s.in_s_quote = 0;
	s.in_d_quote = 0;
	while (s.i < len)
	{
		if (handle_quotes(start, &s))
			continue ;
		if (handle_escape(dest, start, &s, len))
			continue ;
		dest[s.j++] = start[s.i++];
	}
	dest[s.j] = '\0';
	return (dest);
}
