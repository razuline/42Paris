/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:43:24 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/12 19:34:29 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates a WORD token using the optimised method.
 * Performs only a single memory allocation. */
static int	word_token(t_token_lst *lst, char *start, char *end)
{
	char	*final_word;
	int		quote_type;
	int		len;
	char	orig_char;

	quote_type = 0;
	len = end - start;
	if (check_unclosed_quotes_in_word(start, len, &quote_type))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		g_exit_status = 2;
		return (1);
	}
	final_word = extract_and_clean_word(start, len);
	if (!final_word)
		return (1);
	orig_char = *end;
	*end = '\0';
	quote_type = get_quote_type(start);
	*end = orig_char;
	if (create_token(lst, final_word, WORD, quote_type) == NULL)
		return (1);
	return (0);
}

/* Isolates a word and starts its tokenisation. */
int	handle_word(t_token_lst *lst, char **c)
{
	int		result;
	char	*wd_start;
	char	*wd_end;

	wd_start = *c;
	wd_end = find_word_end(wd_start);
	if (wd_start == wd_end)
	{
		*c = wd_end;
		return (0);
	}
	result = word_token(lst, wd_start, wd_end);
	if (result != 0)
		return (result);
	*c = wd_end;
	return (result);
}

/* Creates a token for single operators ('|', '<', '>'). */
int	handle_single_op(t_token_lst *lst, char **c)
{
	if (**c == '|')
	{
		create_token(lst, ft_strdup("|"), PIPE, DEFAULT);
		*c += 1;
		return (1);
	}
	else if (**c == '<')
	{
		create_token(lst, ft_strdup("<"), REDIRECT_IN, DEFAULT);
		*c += 1;
		return (1);
	}
	else if (**c == '>')
	{
		create_token(lst, ft_strdup(">"), REDIRECT_OUT, DEFAULT);
		*c += 1;
		return (1);
	}
	return (0);
}

/* Creates a token for double operators ('<<', '>>'). */
int	handle_double_op(t_token_lst *lst, char **c)
{
	if (**c == '<' && *(*c + 1) == '<')
	{
		create_token(lst, ft_strdup("<<"), HEREDOC, DEFAULT);
		*c += 2;
		return (1);
	}
	else if (**c == '>' && *(*c + 1) == '>')
	{
		create_token(lst, ft_strdup(">>"), APPEND_OUT, DEFAULT);
		*c += 2;
		return (1);
	}
	return (0);
}
