/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:47:11 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/11 15:57:57 by erazumov         ###   ########.fr       */
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

typedef struct	s_game
{
	t_map	map;
	int		moves;
	void	*mlx;
	void	*win;
	void	*player_img;
	void	*floor_img;
	void	*object_img;
	void	*exit_img;
}				t_game;


int	close_game(t_game *game);

#endif
