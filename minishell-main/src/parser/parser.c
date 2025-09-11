/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:55:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/06 15:24:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles a redirection token by creating a redirection structure.
 * Expects the next token to be a WORD representing the filename. */
int	process_redir(t_command *cmd, t_token **tok_ptr)
{
	t_token	*token_file;
	t_redir	*new_redir;

	token_file = (*tok_ptr)->next;
	if (!token_file || token_file->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (1);
	}
	new_redir = create_redir(token_file, (*tok_ptr)->type);
	if (!new_redir)
		return (1);
	add_redir_to_cmd(cmd, new_redir);
	*tok_ptr = token_file->next;
	return (0);
}

/* Main parser logic. Iterates through tokens, parsing each command
 * segment and handling pipes between them. */
t_command	*parser(t_token *token_lst, t_shell *state)
{
	t_command	*cmd_head;
	t_command	*current_cmd;

	if (!token_lst)
		return (NULL);
	if (token_lst->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		state->exit_code = 2;
		return (NULL);
	}
	cmd_head = create_command();
	if (!cmd_head)
		return (NULL);
	current_cmd = cmd_head;
	while (token_lst)
	{
		if (parser_loop(&current_cmd, &token_lst, state) != 0)
			return (parser_error(cmd_head, state));
	}
	return (cmd_head);
}
