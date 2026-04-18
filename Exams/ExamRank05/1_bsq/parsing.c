/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:47:10 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/18 13:57:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	read_header(FILE *fp, t_map *map)
{
	fscanf(fp, "%d %c %c %c", &map->height, &map->empty, &map->obs, &map->full);

	if (&map->height > 0 && &map->height != &map->empty != &map->obs != &map->full)
	{
		return (1);
	}
	fprintf(stderr, "map error\n");
}
