/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:30:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/26 13:29:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIP_H
# define RIP_H

#include <unistd.h>
#include <stdio.h>

void	get_solutions(char *buf, int n, int idx, int balance, int open,
		int close);

#endif
