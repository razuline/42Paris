/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:30:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/09 13:21:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIP_H
# define RIP_H

# include <unistd.h>
# include <stdio.h>

# define MAX_LEN 4096

void	get_solutions(char *buff, int n, int idx, int balance, int open,
		int close);

#endif
