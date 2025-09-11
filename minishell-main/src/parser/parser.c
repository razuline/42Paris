/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:55:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/11 18:55:12 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to handle parsing errors cleanly. */
t_command	*parser_error(t_command *cmd_head, t_shell *state)
{
	state->exit_code = 2;
	free_commands(cmd_head);
	return (NULL);
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
