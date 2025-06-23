/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:01:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/23 12:31:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Taille de buffer pour la lecture */
#define BUFFER_SIZE 4096

/* Compare les 'n' premiers caractères de deux chaînes */
static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s1 == *s2 && --n > 0)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/* Écrit le nombre spécifié d'étoiles sur la sortie standard */
static void	print_stars(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		write(STDOUT_FILENO, "*", 1);
		i++;
	}
}

static int	process_and_write(char *work_buff, int work_len,
		const char *find_str, int find_len)
{
	int	i;
	int	last_print_pos;
	int	limit;

	i = 0;
	last_print_pos = 0;
	limit = work_len - (find_len - 1);
	if ()
}
