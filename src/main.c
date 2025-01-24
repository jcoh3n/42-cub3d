/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/24 14:48:24 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/stat.h>

static int	ft_strendswith(const char *str, const char *suffix)
{
	size_t	str_len;
	size_t	suffix_len;

	if (!str || !suffix)
		return (0);
	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return (0);
	return (!ft_strcmp(str + str_len - suffix_len, suffix));
}

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
	map->floor.r = -1;
	map->floor.g = -1;
	map->floor.b = -1;
	map->ceiling.r = -1;
	map->ceiling.g = -1;
	map->ceiling.b = -1;
	return (map);
}

static void	init_game_values(t_game *game)
{
	if (!game)
		error_exit(ERR_MALLOC);
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(ERR_MALLOC);
	game->win = NULL;
	game->is_running = 0;
	game->window_focused = 1;
	game->map = NULL;            // Initialize the char** map to NULL
	game->map_data = init_map(); // Store t_map* in map_data
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	init_game_values(game);
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
		swap_buffers(game);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	struct stat path_stat;

	if (argc != 2)
		error_exit(ERR_USAGE);
	if (stat(argv[1], &path_stat) == -1)
		error_exit(ERR_FILE);
	if (S_ISDIR(path_stat.st_mode))
		error_exit(ERR_IS_DIR);
	if (!ft_strendswith(argv[1], ".cub"))
		error_exit(ERR_FILE_EXT);
	game = init_game();
	if (!game)
		error_exit(ERR_MALLOC);
	if (!parse_map(argv[1], game->map_data))
		error_exit(ERR_MAP);
	if (!init_window(game))
		error_exit(ERR_WINDOW_INIT);
	game->map = game->map_data->grid;
	setup_window_hooks(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
