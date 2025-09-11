/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_built_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:17:01 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/11 18:54:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_argv(t_command *cmd, t_token **tok_ptr)
{
	int	i;

	i = 0;
	while (*tok_ptr && (*tok_ptr)->type != PIPE)
	{
		if (is_redirection((*tok_ptr)->type))
		{
			if (process_redir(cmd, tok_ptr) != 0)
				return (1);
		}
		else
		{
			cmd->argv[i] = ft_strdup((*tok_ptr)->value);
			if (!cmd->argv[i])
				return (1);
			i++;
			*tok_ptr = (*tok_ptr)->next;
		}
	}
	cmd->argv[i] = NULL;
	return (0);
}

t_redir	*create_redir(t_token *token, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(token->value);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	redir->next = NULL;
	redir->expand = 0;
	redir->is_heredoc = 0;
	if (type == HEREDOC)
	{
		redir->is_heredoc = 1;
		if (token->quote_type != SINGLE_QUOTE
			&& token->quote_type != DOUBLE_QUOTE)
			redir->expand = 1;
	}
	return (redir);
}

/* Handles a redirection token by creating a redirection structure.
 * Expects the next token to be a WORD representing the filename. */
int	process_redir(t_command *cmd, t_token **tok_ptr)
{
	t_token	*token_file;
	t_redir	*new_redir;

	token_file = (*tok_ptr)->next;
	if (!token_file)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (token_file->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token_file->value, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	new_redir = create_redir(token_file, (*tok_ptr)->type);
	if (!new_redir)
		return (1);
	add_redir_to_cmd(cmd, new_redir);
	*tok_ptr = token_file->next;
	return (0);
}
