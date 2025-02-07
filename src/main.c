/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 20:17:29 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

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

static void	check_args(const char *filename, int argc, char **argv)
{
	int	fd;

	if (!filename)
		error_exit(ERR_FILE);
	if (argc != 2)
		error_exit(ERR_USAGE);
	if (!ft_strendswith(filename, EXTENSION_NAME))
		error_exit(ERR_FILE_EXT);
	fd = open(argv[1], O_DIRECTORY | O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		error_exit(ERR_IS_DIR);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit(ERR_FILE);
	close(fd);
}

t_map_data	*init_map(void)
{
	t_map_data	*map;

	map = (t_map_data *)malloc(sizeof(t_map_data));
	if (!map)
		error_exit(ERR_MALLOC);
	ft_memset(map, 0, sizeof(t_map_data));
	map->floor.r = -1;
	map->floor.g = -1;
	map->floor.b = -1;
	map->ceiling.r = -1;
	map->ceiling.g = -1;
	map->ceiling.b = -1;
	map->player_start_x = -1;
	map->player_start_y = -1;
	map->player_x = -1;
	map->player_y = -1;
	return (map);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		error_exit(ERR_MALLOC);
	ft_memset(game, 0, sizeof(t_game));
	game->renderer.mlx = mlx_init();
	if (!game->renderer.mlx)
		error_exit(ERR_MALLOC);
	game->state.is_running = 1;
	game->state.window_focused = 1;
	game->state.last_frame = get_time();
	game->input.mouse_sensitivity = MOUSE_SENSITIVITY;
	game->map_data = init_map();
	if (!game->map_data)
		error_exit(ERR_MALLOC);
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	check_args(argv[1], argc, argv);
	game = init_game();
	if (!game)
		error_exit(ERR_MALLOC);
	parse_map(argv[1], game->map_data);
	if (!init_window(game))
	{
		cleanup_game(game);
		error_exit(ERR_WINDOW_INIT);
	}
	game->map = game->map_data->grid;
	init_player(game);
	init_minimap(game);
	game->state.is_running = 1;
	mlx_loop_hook(game->renderer.mlx, game_loop, game);
	mlx_loop(game->renderer.mlx);
	cleanup_game(game);
	return (0);
}
