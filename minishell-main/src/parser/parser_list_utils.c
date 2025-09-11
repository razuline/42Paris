/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:22:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/06 15:19:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Allocates and initializes a new command structure (t_command). */
t_command	*create_command(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

/* Appends a redirection structure to a command's redirection list. */
void	add_redir_to_cmd(t_command *cmd, t_redir *new_redir)
{
	t_redir	*curr;

	if (cmd->redir == NULL)
		cmd->redir = new_redir;
	else
	{
		curr = cmd->redir;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_redir;
	}
}

/* Counts the number of commands in a linked list. */
int	count_commands(t_command *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

/* Checks if a command list contains a pipe (i.e., has more
 * than one command). */
int	has_pipe(t_command *cmds)
{
	return (cmds && cmds->next != NULL);
}

/* Checks if a token type is a redirection type. */
int	is_redirection(int type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT || type == APPEND_OUT
		|| type == HEREDOC);
}
