/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 00:57:29 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *message)
{
	printf("Error\n%s\n", message);
	exit(1);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		error_exit(ERR_MALLOC);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_dir = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->north.img = NULL;
	map->south.img = NULL;
	map->east.img = NULL;
	map->west.img = NULL;
	map->north.path = NULL;
	map->south.path = NULL;
	map->east.path = NULL;
	map->west.path = NULL;
	return (map);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		error_exit(ERR_MALLOC);
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(ERR_MALLOC);
	game->win = NULL;
	game->map = init_map();
	game->is_running = 0;
	game->window_focused = 1;
	return (game);
}

int	game_loop(t_game *game)
{
	if (!game->is_running)
		return (0);
	if (game->window_focused)
	{
		update_player(game);
		clear_buffer(&game->img);
		draw_test_pattern(game);
		swap_buffers(game);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error_exit(ERR_USAGE);
	game = init_game();
	if (!game)
		error_exit(ERR_MALLOC);
	if (!parse_map(argv[1], game->map))
		error_exit(ERR_MAP);
	if (!init_window(game))
		error_exit(ERR_WINDOW_INIT);
	setup_window_hooks(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
