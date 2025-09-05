/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:24:53 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/05 14:10:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int		ft_strlen(char *str);
void	print_error(char *msg, char *arg);
void	fatal_error(void);
int		handle_cd(char **args);
void	child_execute(char **cmd, char **envp, int fd_in, int *fd_pipe,
			int has_pipe);
void	wait_for_children(void);
void	execute_sequence(char **args, char **envp);

#endif
