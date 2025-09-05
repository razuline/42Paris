/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:27:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/05 18:28:51 by erazumov         ###   ########.fr       */
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

/* Helper function containing the main parser loop's logic. */
int	parser_loop(t_command **current_cmd, t_token **token_lst, t_shell *state)
{
	int	argc;

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
