/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:56 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 14:18:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/includes/libft.h"

# include <signal.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/* Server functions */
void	handler(int signal, siginfo_t *info, void *context);

/* Client functions */
void	send_char(char c, int pid);

#endif
