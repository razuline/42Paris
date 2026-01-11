/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:29:01 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/06 20:30:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Destroys MLX window and images, then frees all allocated memory.
** Finally exits the program.
*/
int	close_game(t_game *game)
{
	if (!game || !game->mlx_data)
		return (0);
	free_game(game);
	exit(0);
	return (0);
}
