/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:40:50 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 13:57:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"

# define TILE_SIZE 64

// Символы карты
# define WALL '1'
# define FLOOR '0'
# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define EXIT 'E'
# define ENEMY 'X'

#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307

# define PLAYER_ANIM_SPEED 10
# define COLLECT_ANIM_SPEED 15
# define ENEMY_ANIM_SPEED 12
# define ENEMY_MOVE_SPEED 30

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_anim
{
	void	**frames;
	int		count;
	int		current_frame;
}	t_anim;

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*exit_open;
	void	*exit_closed;
	t_anim	player;
	t_anim	collectible;
	t_anim	enemy;
}	t_textures;

typedef struct s_game
{
	void		*mlx;                // Указатель на инстанс MLX
	void		*win;                // Указатель на окно MLX
	t_map		map;                 // Карта игры
	t_point		player_pos;          // Текущая позиция игрока
	int			collectibles_total;  // Всего коллекционных предметов
	int			collectibles_current;// Сколько осталось собрать
	int			moves;
	t_textures	tex;
	t_point		*enemy_pos;          // Массив позиций врагов (бонус)
	int			enemy_count;         // Количество врагов (бонус)
	int			frame_counter;       // Счетчик кадров для анимации/логики (бонус)
	int			game_over;
}	t_game;

// main_bonus.c
void	check_arguments(int ac, char **av);
void	init_game_struct(t_game *game);
void	run_game(t_game *game);

// error_bonus.c
void	exit_error(t_game *game, char *message);
void	print_error(char *message);

// map_reader_bonus.c
void	read_map(char *filename, t_game *game);

// map_validation_check_bonus.c
void	validate_map_structure(t_game *game);

// map_validation_path_bonus.c
void	validate_path(t_game *game);

// init_bonus.c
void	init_game(t_game *game);
void	load_textures(t_game *game);
void	init_animation(t_anim *anim, int frame_count);

// render_bonus.c
int		render_frame(t_game *game);
void	put_image_to_window(t_game *game, void *img, int x, int y);
void	draw_move_counter(t_game *game);

// hooks_bonus.c
void	setup_hooks(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_window_close(t_game *game);
int		game_loop(t_game *game);

// player_movement_bonus.c
void	try_move_player(t_game *game, int dx, int dy);

// game_logic_bonus.c
void	collect_item(t_game *game, int x, int y);
void	check_exit(t_game *game, int x, int y);
void	check_enemy_collision(t_game *game, int x, int y);
void	win_game(t_game *game);
void	lose_game(t_game *game);

// animation_bonus.c
void	update_animations(t_game *game);
void	*get_current_frame(t_anim *anim);
void	destroy_animation(t_game *game, t_anim *anim);

// enemy_bonus.c
void	find_enemies(t_game *game);
void	update_enemies(t_game *game);

// cleanup_bonus.c
void	cleanup_game(t_game *game);
void	exit_game(t_game *game, int exit_code);
void	free_map_grid(char **grid, int height);
void    destroy_textures(t_game *game);


// utils_bonus.c (если есть)
// ...

#endif
