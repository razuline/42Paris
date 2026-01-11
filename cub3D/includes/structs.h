/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 09:52:14 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/10 17:56:39 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <math.h>

/** =============================== CONSTANTS ============================== **/
/*
** BLOCK: size of one grid square in pixels (64x64)
** WIN_WIDTH/HEIGHT: window resolution (1280x720)
** PI: mathematical constant for angle calculations
** FOV: Field of View in radians (60 degrees = ~1.047 rad)
*/
# define BLOCK 64
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define PI 3.14159265358979323846
# define FOV 1.0471975511965976f

/** ============================== STRUCTURES ============================== **/

/** -------------------------------- VECTOR -------------------------------- **/
/* Used for 2D positions and directions
** Used for player position, movement calculations */
typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

/** -------------------------------- PLAYER -------------------------------- **/
/* pos: Current coordinates on the map (x, y)
** dir_x/y: Direction vector representing where the player is looking
** plane_x/y: Camera plane vector used to calculate FOV and ray direction
** angle: Orientation in radians (used for initial setup or math)
** key_up/down: Movement flags for forward (W) and backward (S)
** key_left/right: Movement flags for strafing left (A) and right (D)
** left/right_rotate: Rotation flags for arrow keys */
typedef struct s_player
{
	t_vector	pos;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		angle;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
}	t_player;

/** --------------------------------- WALL --------------------------------- **/
/* start: starting Y-coordinate of the wall slice on screen
** end: ending Y-coordinate of the wall slice on screen
** tex_x: exact horizontal coordinate on the texture to sample
** height: raw vertical height of the wall based on distance */
typedef struct s_wall
{
	int		start;
	int		end;
	int		tex_x;
	float	height;
}	t_wall;

/** --------------------------------- MAP ---------------------------------- **/
/* grid: 2D character array representing the map layout ('1', '0', 'NSEW')
** width: Maximum number of columns across the entire map
** height: Total number of rows (lines) in the map
** line_len: Array storing the length of each individual row for validation
** no_path: Allocated string for the North texture file path
** so_path: Allocated string for the South texture file path
** we_path: Allocated string for the West texture file path
** ea_path: Allocated string for the East texture file path
** floor_color: Final integer color value for the floor (pre-calculated)
** ceiling_color: Final integer color value for the ceiling (pre-calculated)
** f_rgb: Raw RGB data storage for the floor color
** c_rgb: Raw RGB data storage for the ceiling color */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		*line_len;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	int		f_rgb;
	int		c_rgb;
}	t_map;

/** ------------------------------- TEXTURES ------------------------------- **/
/* Texture structure for storing file paths before loading
** Stores pointers to texture file paths
** Paths are allocated with malloc, must be freed */
typedef struct s_texture
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		line_len;
	int		endian;
	int		bpp;
}	t_texture;

/** ---------------------------------- DDA --------------------------------- **/
/* Data for the Digital Differential Analyser algorithm */
typedef struct s_dda
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

/** ------------------------------ RGB COLORS ------------------------------ **/
/* Used for floor (F) and ceiling (C) colors from .cub file
** Each component 0-255
** Stored as int (-1 means "not set yet") */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/** ------------------------------- MLX DATA ------------------------------- **/
/* mlx: pointer to MLX connection (created by mlx_init)
** ptr_mlx: main MLX instance (returned by mlx_init)
** window: window pointer (created by mlx_new_window)
** image: drawable image buffer (for off-screen rendering)
** image_add: memory address of image buffer for pixel access
** bits_per_pixel: color depth
** line_length: bytes per row
** endian: byte order */
typedef struct s_mlx_data
{
	void	*ptr_mlx;
	void	*window;
	void	*image;
	char	*image_add;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_data;

/** ------------------------- MAIN GAME STRUCTURE -------------------------- **/
/* Contains all game state
** player: player position, angle, input flags
** map: parsed map grid with dimensions
** mlx_data: MLX window and rendering buffers
** tex[4]: texture array [0]=NO, [1]=SO, [2]=WE, [3]=EA
** floor: RGB values for floor (C parameter)
** ceiling: RGB values for ceiling (F parameter) */
typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_mlx_data	*mlx_data;
	t_texture	tex[4];
	t_color		floor;
	t_color		ceiling;
}	t_game;

/** ----------------------TO MANAGE COLLISION --------------------- **/
/* Used in one function only*/

typedef struct s_collision
{
	float	new_x;
	float	new_y;
	float	perp_x;
	float	perp_y;
}	t_collision;

#endif
