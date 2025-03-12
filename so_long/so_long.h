/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:47:11 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/12 11:42:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
/* # include <mlx.h> */
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# define SQUARE_SIZE 32

typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		object;
	int		exit_x;
	int		exit_y;
}				t_map;

typedef struct	s_images
{
	void	*player_img;
	void	*wall_img;
	void	*floor_img;
	void	*object_img;
	void	*exit_img;
}				t_images;


typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_images	img;
}				t_game;

void	load_images(t_game *game);
int		init_game(t_game *game, char *map_file);
void	render_square(t_game *game, char square, int x, int y);
void	render_game(t_game *game);

void	free_game(t_game *game);
void	free_map(t_map *map);
int		close_game(t_game *game);

#endif
