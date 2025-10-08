/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:28:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/12 19:50:10 by preltien         ###   ########.fr       */
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

int	check_unclosed_quotes(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->unclosed)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
			g_exit_status = 2;
			return (1);
		}
		token_lst = token_lst->next;
	}
	return (0);
}

/* Handles a redirection token by creating a redirection structure.
 * Expects the next token to be a WORD representing the filename. */

int	process_redir(t_command *cmd, t_token **tok_ptr)
{
	t_token	*token_file;
	t_redir	*new_redir;

	token_file = (*tok_ptr)->next;
	if (!token_file || token_file->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!token_file)
			ft_putstr_fd("newline", 2);
		else if (token_file->value)
			ft_putstr_fd(token_file->value, 2);
		else
			ft_putstr_fd("?", 2);
		ft_putstr_fd("'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	new_redir = create_redir(token_file, (*tok_ptr)->type);
	if (!new_redir)
		return (1);
	add_redir_to_cmd(cmd, new_redir);
	*tok_ptr = token_file->next;
	return (0);
}
