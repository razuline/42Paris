/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:30:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/15 15:54:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIP_H
# define RIP_H

#include <unistd.h>
#include <stdio.h>

int		ft_strlen(char *str);
void	generate(char *str, int idx, int left_rem, int right_rem, int balance);

#endif
