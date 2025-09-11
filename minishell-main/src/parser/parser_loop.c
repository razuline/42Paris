/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 20:20:35 by erazumov         ###   ########.fr       */
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
		free_argv(cmd->argv);
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
		return (1);
	}
	(*cmd)->next = create_command();
	if (!(*cmd)->next)
		return (1);
	*cmd = (*cmd)->next;
	return (0);
}

/* Helper function containing the main parser loop's logic. */
int	parser_loop(t_command **current_cmd, t_token **token_lst, t_shell *state)
{
	int	argc;

	(void)state;
	while (*token_lst)
	{
		argc = count_args(*token_lst);
		if (fill_command(*current_cmd, token_lst, argc) != 0)
			return (1);
		if (*token_lst && (*token_lst)->type == PIPE)
		{
			if (handle_pipe_token(current_cmd, token_lst) != 0)
				return (1);
		}
	}
	return (0);
}
