/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clean_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:38:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 18:05:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles quote characters (' and ") while parsing a word.
 * It updates the quote state (open/closed) and advances the 'i' index. */
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
 * Copies the next character if it's a special char inside double quotes. */
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

/* (PASS 1) Calculates the final length of the string after cleaning. */
static int	calculate_cleaned_len(const char *start, int len)
{
	t_clean_state	s;
	int				final_len;
	char			next_char;

	s = (t_clean_state){0, 0, 0, 0};
	final_len = 0;
	while (s.i < len)
	{
		if ((start[s.i] == '\'' && !s.in_d_quote)
			|| (start[s.i] == '"' && !s.in_s_quote))
		{
			handle_quotes(start, &s);
			continue ;
		}
		if (start[s.i] == '\\' && s.in_d_quote && s.i + 1 < len)
		{
			next_char = start[s.i + 1];
			if (next_char == '$' || next_char == '"' || next_char == '\\')
				s.i++;
		}
		final_len++;
		s.i++;
	}
	return (final_len);
}

/* (PASS 2) Fills the destination string with the cleaned characters. */
static void	fill_cleaned_word(char *dest, const char *start, int len)
{
	t_clean_state	s;

	s = (t_clean_state){0, 0, 0, 0};
	while (s.i < len)
	{
		if (handle_quotes(start, &s))
			continue ;
		if (handle_escape(dest, start, &s, len))
			continue ;
		dest[s.j++] = start[s.i++];
	}
	dest[s.j] = '\0';
}

/* Orchestrates the cleaning of a word using the two-pass approach. */
char	*extract_and_clean_word(const char *start, int len)
{
	char	*dest;
	int		cleaned_len;

	cleaned_len = calculate_cleaned_len(start, len);
	dest = malloc(sizeof(char) * (cleaned_len + 1));
	if (!dest)
		return (NULL);
	fill_cleaned_word(dest, start, len);
	return (dest);
}
