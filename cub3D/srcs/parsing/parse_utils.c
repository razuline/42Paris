/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:45 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/06 20:09:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Remove trailing newline character from string.
** Modifies string in-place.
** Safe if no newline present.
*/
void	remove_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/*
** Replace all tab characters with spaces.
** Used to normalise whitespace in config lines.
** Modifies string in-place.
*/
void	replace_tabs(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

/*
** Count number of non-null, non-empty elements in array.
** Used to validate config line format.
** Returns number of elements.
*/
int	count_elem(char **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}

/*
** Check if character is valid in map.
** Valid: '0' (empty), '1' (wall), ' ' (void), 'N/S/E/W' (player).
** Returns 1 if valid, 0 if invalid.
*/
int	is_valid_char(char c)
{
	return (ft_strchr("01 NSEW", c) != NULL);
}

/*
** Free all strings in array and array itself.
** Safe to call on NULL pointer.
** Typically used after ft_split.
*/
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
