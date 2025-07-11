/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   given_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:00:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/11 17:00:59 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL
# define GNL

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

#endif
