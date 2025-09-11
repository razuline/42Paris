/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:27:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/06 15:30:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees a NULL-terminated argument vector (argv) and all its strings. */
void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/* Frees the memory of a linked list of redirections. */
static void	free_redir(t_redir *redir_head)
{
	t_redir	*curr;
	t_redir	*next;

	curr = redir_head;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->file);
		free(curr);
		curr = next;
	}
}

/* Frees the memory of a linked list of commands and all their content
 * (argv and redirection lists). */
void	free_commands(t_command *cmd_head)
{
	t_command	*curr;
	t_command	*next;

	curr = cmd_head;
	while (curr != NULL)
	{
		next = curr->next;
		free_redir(curr->redir);
		free_argv(curr->argv);
		free(curr);
		curr = next;
	}
}

/* Helper function to handle parsing errors cleanly. */
t_command	*parser_error(t_command *cmd_head, t_shell *state)
{
	state->exit_code = 2;
	free_commands(cmd_head);
	return (NULL);
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
int	parser_loop(t_command **current_cmd, t_token **token_lst,
	t_shell *state)
{
	int	argc;

	(void)state;
	argc = count_args(*token_lst);
	if (fill_command(*current_cmd, token_lst, argc) != 0)
		return (1);
	if (*token_lst && (*token_lst)->type == PIPE)
	{
		if (handle_pipe_token(current_cmd, token_lst) != 0)
			return (1);
	}
	return (0);
}
