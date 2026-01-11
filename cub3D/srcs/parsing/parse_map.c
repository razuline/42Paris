/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:54:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/10 14:20:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Helper to find the longest line in the map list.
** Sets the global width for grid normalisation.
*/
static int	get_max_width(t_list *lst)
{
	int	max;
	int	current_len;

	max = 0;
	while (lst)
	{
		current_len = ft_strlen(lst->content);
		if (current_len > max)
			max = current_len;
		lst = lst->next;
	}
	return (max);
}

/*
** Converts the linked list to a rectangular 2D grid.
** All lines are padded to game->map.width to ensure DDA safety.
*/
int	convert_list_to_grid(t_game *game, t_list *lst)
{
	int		i;
	t_list	*tmp;

	if (!game || !lst)
		return (0);
	game->map.height = ft_lstsize(lst);
	game->map.width = get_max_width(lst);
	if (game->map.height == 0 || !alloc_map_arrays(game))
		return (0);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		game->map.grid[i] = normalise_line((char *)tmp->content,
				game->map.width);
		if (!game->map.grid[i])
			return (0);
		game->map.line_len[i] = game->map.width;
		i++;
		tmp = tmp->next;
	}
	return (1);
}

/*
** Reads map lines from FD and stores them in a linked list.
*/
static int	read_map_loop(int fd, t_list **lst_map)
{
	char	*line;
	t_list	*node;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		remove_newline(line);
		node = ft_lstnew(line);
		if (!node)
			return (free(line), ft_lstclear(lst_map, free), 0);
		ft_lstadd_back(lst_map, node);
	}
	return (1);
}

/*
** Main entry for map parsing called by the file parser.
*/
int	parse_map(t_game *game, int fd, char *first_line)
{
	t_list	*lst_map;

	if (!first_line)
		return (0);
	remove_newline(first_line);
	lst_map = ft_lstnew(ft_strdup(first_line));
	if (!lst_map)
		return (0);
	if (!read_map_loop(fd, &lst_map))
		return (0);
	if (!convert_list_to_grid(game, lst_map))
	{
		ft_lstclear(&lst_map, free);
		return (0);
	}
	ft_lstclear(&lst_map, free);
	return (1);
}
