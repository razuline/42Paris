/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:27:20 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/06 15:52:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Allocates memory for MLX data and initialises the MLX instance.
** Returns the initialised structure or NULL on failure.
*/
t_mlx_data	*init_mlx_data(void)
{
	t_mlx_data	*mlx_data;

	mlx_data = malloc(sizeof(t_mlx_data));
	if (!mlx_data)
		return (NULL);
	mlx_data->ptr_mlx = mlx_init();
	if (!mlx_data->ptr_mlx)
	{
		free(mlx_data);
		return (NULL);
	}
	mlx_data->window = NULL;
	mlx_data->image = NULL;
	mlx_data->image_add = NULL;
	mlx_data->bits_per_pixel = 0;
	mlx_data->line_length = 0;
	mlx_data->endian = 0;
	return (mlx_data);
}
