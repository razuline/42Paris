/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:56 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/15 14:00:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
#define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

/* Server functions */
void	signal_handler(int sig);

/* Client functions */
void	send_bit(char c, int pid);

#endif
