/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 14:33:23 by jcohen           ###   ########.fr       */
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

	map = (t_map_data *)ft_calloc(1, sizeof(t_map_data));
	if (!map)
		error_exit(ERR_MALLOC);
	map->floor.r = -1;
	map->floor.g = -1;
	map->floor.b = -1;
	map->ceiling.r = -1;
	map->ceiling.g = -1;
	map->ceiling.b = -1;
	return (map);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		error_exit(ERR_MALLOC);
	// Initialize renderer
	game->renderer.mlx = mlx_init();
	if (!game->renderer.mlx)
		error_exit(ERR_MALLOC);
	game->renderer.render_flags = 0;
	game->renderer.current_texture = NULL;
	// Initialize game state
	game->state.is_running = 1;
	game->state.window_focused = 1;
	game->state.mouse_captured = 0;
	game->state.last_frame = get_time();
	game->state.delta_time = 0;
	game->state.fps = 0;
	game->state.status_anim_frame = 0;
	game->state.status_transitioning = 0;
	// Initialize input
	ft_memset(&game->input, 0, sizeof(t_input));
	game->input.mouse_sensitivity = MOUSE_SENSITIVITY;
	// Initialize map data
	game->map_data = init_map();
	if (!game->map_data)
		error_exit(ERR_MALLOC);
	// Initialize player with default values
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	return (game);
}

int	game_loop(t_game *game)
{
	if (!game->state.is_running)
	{
		mlx_loop_end(game->renderer.mlx);
		return (1);
	}
	update_player_position(game);
	render_frame(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	check_args(argv[1], argc, argv);
	game = init_game();
	if (!game)
		error_exit(ERR_MALLOC);
	// Parse map and initialize game components
	parse_map(argv[1], game->map_data);
	if (!init_window(game))
		error_exit(ERR_WINDOW_INIT);
	game->map = game->map_data->grid;
	init_player(game);
	init_minimap(game);
	// Start game loop
	game->state.is_running = 1;
	mlx_loop_hook(game->renderer.mlx, game_loop, game);
	mlx_loop(game->renderer.mlx);
	cleanup_game(game);
	return (0);
}
