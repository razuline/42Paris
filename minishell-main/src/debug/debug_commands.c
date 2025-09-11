/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:06:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/09 19:56:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include "minishell.h"

/* (HELPER) Prints the argument vector (argv) of a command. */
static void	print_argv(char **argv)
{
	int	i;

	i = 0;
	printf("  \033[0;36mArguments (argv):\033[0m\n");
	if (argv == NULL)
	{
		printf("    -> (null)\n");
		return ;
	}
	while (argv[i] != NULL)
	{
		printf("    argv[%d]: \"%s\"\n", i, argv[i]);
		i++;
	}
}

/* (HELPER) Prints the redirection list of a command. */
static void	print_redirections(t_redir *redir_lst)
{
	t_redir	*curr;

	curr = redir_lst;
	printf("  \033[0;36mRedirections:\033[0m\n");
	if (redir_lst == NULL)
	{
		printf("    -> (none)\n");
		return ;
	}
	while (curr != NULL)
	{
		printf("    -> TYPE: %-12s, FILE: \"%s\"\n",
			get_type_name(curr->type),
			curr->file);
		curr = curr->next;
	}
}

/* Prints the list of parsed commands for debugging purposes. */
void	debug_print_commands(t_command *cmd_head)
{
	t_command	*curr_cmd;
	int			i;

	curr_cmd = cmd_head;
	i = 1;
	printf("\n\033[1;35m--- COMMAND LIST ---\033[0m\n");
	if (!cmd_head)
	{
		printf(" (empty)\n");
		return ;
	}
	while (curr_cmd != NULL)
	{
		printf("\033[1;33m--- Command %d ---\033[0m\n", i);
		print_argv(curr_cmd->argv);
		print_redirections(curr_cmd->redir);
		curr_cmd = curr_cmd->next;
		i++;
	}
	printf("\033[1;35m--------------------\033[0m\n\n");
}

#endif
