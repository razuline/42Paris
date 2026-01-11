/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:16:03 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/10 14:49:42 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/** =========================== PARSING FUNCTIONS ========================== **/
/**            Main entry point for reading and parsing .cub file            **/

int		parse_file(char *path, t_game *game);
void	init_game_struct(t_game *game);

/** ============================ TEXTURE PARSING =========================== **/
/**            Parse texture paths (NO/SO/WE/EA) from config lines           **/

int		parse_texture(t_game *game, char *line);

/** ============================= COLOR PARSING ============================ **/
/**           Parse RGB colors (F/C <r>,<g>,<b>) from config lines           **/

int		parse_color(t_color *color, char *line);

/** ============================== MAP PARSING ============================= **/
/**             Parse map grid from file and convert to 2D array             **/

int		parse_map(t_game *game, int fd, char *first_line);
int		convert_list_to_grid(t_game *game, t_list *lst);

/** ============================= MAP VALIDATION =========================== **/
/**                 Validate parsed map content and structure                **/

int		valid_map(t_game *game);
int		valid_chars(t_game *game);
int		is_valid_char(char c);
int		check_map_closed(t_game *game);
int		flood_fill_iter(char **map, int start_x, int start_y, int height);
int		run_map_checks(t_game *game);

/** ============================ PLAYER VALIDATION ========================= **/
/**                 Find and validate player position in map                 **/

int		valid_players(t_game *game);

/** ============================ UTILITY FUNCTIONS ========================= **/
/**                       Helper functions for parsing                       **/

void	fill_with_spaces(char *str, int start, int end);
char	*normalise_line(char *content, int max_width);
int		alloc_map_arrays(t_game *game);
void	remove_newline(char *line);
void	replace_tabs(char *line);
int		count_elem(char **arr);
void	free_tab(char **tab);
void	free_game(t_game *game);

#endif