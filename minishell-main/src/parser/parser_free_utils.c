/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:28:46 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/05 19:10:49 by erazumov         ###   ########.fr       */
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
