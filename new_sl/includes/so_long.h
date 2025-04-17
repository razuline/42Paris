/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:55:51 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 18:34:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"

# define TILE_SIZE 32

# define WALL '1'
# define FLOOR '0'
# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define EXIT 'E'

#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*collect;
	void	*player;
	void	*exit_open;
	void	*exit_closed;
}			t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_point		player_pos;
	int			collect_total;
	int			collect_curr;
	int			moves;
	t_textures	tex;
	int			exit_access;
}			t_game;

/* main.c */
void	check_args(int ac, char **av);
void	init_game_struct(t_game *game);
void	run_game(t_game *game);

/* Error */
void	exit_error(t_game *game, char *msg);
void	print_error(char *msg);

/* Map */
void	read_map(char *filename, t_game *game);
void	valid_map_struct(t_game *game);
void	valid_path(t_game *game);

// init.c
void	init_game(t_game *game);
void	load_textures(t_game *game);

// render.c
int		render_frame(t_game *game);
void	draw_map(t_game *game);
void	draw_player(t_game *game);
void	image_to_window(t_game *game, void *img, int x, int y);


// hooks.c
void	setup_hooks(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		window_close(t_game *game);

// player_movement.c
void	try_move_player(t_game *game, int dx, int dy);

// game_logic.c
void	collect_item(t_game *game, int x, int y);
void	check_exit(t_game *game, int x, int y);
void	win_game(t_game *game);

// cleanup.c
void	cleanup_game(t_game *game);
void	exit_game(t_game *game, int exit_code);
void	free_map_grid(char **grid, int height);
void    destroy_textures(t_game *game);

/* Utils */
void	trim_newline(char *line);
int		process_dimen_line(char *line, t_game *game, int *first_line);
void	cleanup_fill_error(t_game *game, int count);
int		check_remain_lines(int fd);
int		allocate_grid(t_game *game);
int		check_horiz_walls(t_game *game);
int		check_vert_walls(t_game *game);
int		is_valid_char(char c);
void	update_counts(char c, t_game *game, int x, int y, int counts[3]);
int		final_count_check(t_game *game, int counts[3]);
int		copy_map_grid(t_game *game, char ***grid_copy_ptr);
void	free_grid_copy(char **grid_copy, int height);

#endif
