/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:55:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/24 14:34:03 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles a redirection token by creating a redirection structure.
 * Expects the next token to be a WORD representing the filename. */
static int	process_redir(t_command *cmd, t_token **tok_ptr)
{
	t_token	*token_file;
	t_redir	*new_redir;

	token_file = (*tok_ptr)->next;
	if (!token_file || token_file->type != WORD)
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n",
				2), 1);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (1);
	new_redir->file = ft_strdup(token_file->value);
	if (!new_redir->file)
	{
		free(new_redir);
		return (1);
	}
	new_redir->type = (*tok_ptr)->type;
	new_redir->next = NULL;
	new_redir->expand = (new_redir->type == HEREDOC
			&& token_file->quote_type != SINGLE_QUOTE);
	add_redir_to_cmd(cmd, new_redir);
	*tok_ptr = token_file->next;
	return (0);
}

/* (HELPER) First pass: counts the number of arguments (WORD tokens)
 * for a single command segment (until a pipe or the end). */
static int	count_args(t_token *token)
{
	int	argc;

	argc = 0;
	while (token && token->type != PIPE)
	{
		if (is_redirection(token->type))
		{
			if (token->next)
				token = token->next;
		}
		else
			argc++;
		token = token->next;
	}
	return (argc);
}

/* (HELPER) Second pass: allocates and fills the argv array for a
 * single command and handles its redirections. */
static int	fill_command(t_command *cmd, t_token **tok_ptr, int argc)
{
	int	i;

	i = 0;
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		return (1);
	while (*tok_ptr && (*tok_ptr)->type != PIPE)
	{
		if (is_redirection((*tok_ptr)->type))
		{
			if (process_redir(cmd, tok_ptr) != 0)
				return (1);
		}
		else
		{
			cmd->argv[i++] = ft_strdup((*tok_ptr)->value);
			*tok_ptr = (*tok_ptr)->next;
		}
	}
	cmd->argv[i] = NULL;
	return (0);
}

/* (HELPER) After parsing a command, this function checks for a pipe.
 * If found, it creates and links the next command structure. */
static int	handle_pipe_token(t_command **cmd, t_token **token)
{
	if (!*token || (*token)->type != PIPE)
		return (0);
	*token = (*token)->next;
	if (!*token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	(*cmd)->next = create_command();
	if (!(*cmd)->next)
		return (1);
	*cmd = (*cmd)->next;
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
		if (fill_command(current_cmd, &token_lst, count_args(token_lst))
			|| handle_pipe_token(&current_cmd, &token_lst))
		{
			state->exit_code = 2;
			return (free_commands(cmd_head), NULL);
		}
	}
	return (cmd_head);
}
