/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:45:46 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/10 14:46:44 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "structs.h"
# include "parsing.h"

/** ======================= INITIALISATION & CLEANUP ======================= **/
/**          Functions to set up MLX window and clean up resources           **/

void		init_mlx(t_game *game);
int			close_game(t_game *game);
t_mlx_data	*init_mlx_data(void);
int			load_texture(t_game *game, t_texture *tex, char *path);
int			load_all_textures(t_game *game);

/** ============================ INPUT HANDLING ============================ **/
/**             Keyboard event handlers and input initialisation             **/

int			init_hooks(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);

/** =========================== PLAYER MOVEMENT ============================ **/
/**                Functions for player position and rotation                **/

void		move_player(t_player *player, t_game *game);
void		set_player_position(t_game *game);
void		set_angle(t_player *player, char c);

/** ========================= RENDERING & DRAWING ========================== **/
/**              Core drawing functions for 2D and 3D rendering              **/

int			draw_loop(t_game *game);
void		clear_image(t_game *game);
void		put_pixel(int x, int y, int color, t_game *game);
void		draw_line(t_player *player, t_game *game, int col);
void		draw_c_f(t_game *game, int col, int start_y, int end_y);

/** ======================= RAYCASTING & 3D RENDERING ====================== **/
/**            Ray casting algorithm for 3D perspective rendering            **/

void		init_dda(t_dda *d, t_player *p, float camera_x);
void		draw_wall_slice(int col, t_dda *d, t_game *game);
int			get_tex_index(t_dda *d);

/** =============================== UTILITIES ============================== **/
/**             Helper functions for collision detection and math            **/

int			touch(float px, float py, t_game *game);
int			rgb_to_int(t_color color);

#endif