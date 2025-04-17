/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:02:08 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 14:17:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->player_pos.x = 0;
	game->player_pos.y = 0;
	game->collect_total = 0;
	game->collect_curr = 0;
	game->moves = 0;
	ft_memset(&game->tex, 0, sizeof(t_textures));
	game->exit_access = 0;
}

void	check_args(int ac, char **av)
{
	int		len;
	char	*ext;

	if (ac != 2)
	{
		print_error("Usage: ./so_long <map_file.ber>");
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(av[1]);
	if (len < 5)
	{
		print_error("Error: Invalid map file name.");
		exit(EXIT_FAILURE);
	}
	ext = av[1] + len - 4;
	if (ft_strcmp(ext, ".ber") != 0)
	{
		print_error("Error: Map file must have a '.ber' extension.");
		exit(EXIT_FAILURE);
	}
}

void	run_game(t_game *game)
{
	setup_hooks(game);
	render_frame(game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	check_args(ac, av);
	init_game_struct(&game);
	read_map(av[1], &game);
	valid_map_struct(&game);
	valid_path(&game);
	init_game(&game);
	ft_printf("Game started! Collect %d items.\n", game.collect_total);
	run_game(&game);
	cleanup_game(&game);
	return (EXIT_SUCCESS);
}
