/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:55:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/12 20:05:35 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	fill_command(t_command *cmd, t_token **tok_ptr, int argc)
{
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		return (1);
	if (fill_argv(cmd, tok_ptr) != 0)
	{
		cmd->argv = NULL;
		g_exit_status = 2;
		return (1);
	}
	if (!cmd->argv[0] && cmd->redir)
	{
		free(cmd->argv);
		cmd->argv = NULL;
	}
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
		g_exit_status = 2;
		return (1);
	}
	(*cmd)->next = create_command();
	if (!(*cmd)->next)
		return (1);
	*cmd = (*cmd)->next;
	return (0);
}

static int	check_parser(t_token *token_lst)
{
	if (!token_lst)
		return (0);
	if (check_unclosed_quotes(token_lst))
		return (1);
	if (token_lst->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

/* Main parser logic. Iterates through tokens, parsing each command
 * segment and handling pipes between them. */
t_command	*parser(t_token *token_lst)
{
	t_command	*cmd_head;
	t_command	*current_cmd;

	if (check_parser(token_lst))
		return (NULL);
	cmd_head = create_command();
	if (!cmd_head)
		return (NULL);
	current_cmd = cmd_head;
	while (token_lst)
	{
		if (fill_command(current_cmd, &token_lst, count_args(token_lst))
			|| handle_pipe_token(&current_cmd, &token_lst))
		{
			g_exit_status = 2;
			free_commands(cmd_head);
			return (NULL);
		}
	}
	return (cmd_head);
}
