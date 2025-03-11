/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:51:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/11 15:59:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	load_images(t_game *game)
{
	int	size;

	size = SQUARE_SIZE;
	game->player_img = mlx_xpm_file_to_img(game->mlx, "assets/player.xpm", &size, &size);
	
	
}