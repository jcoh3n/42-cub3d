/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/28 17:21:19 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
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

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
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
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(ERR_MALLOC);
	game->map_data = init_map();
	game->window_focused = 1;
	return (game);
}

int	game_loop(t_game *game)
{
	if (!game->is_running)
	{
		mlx_loop_end(game->mlx);
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
	parse_map(argv[1], game->map_data);
	if (!init_window(game))
		error_exit(ERR_WINDOW_INIT);
	game->map = game->map_data->grid;
	init_minimap(game);
	setup_window_hooks(game);
	game->is_running = 1;
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	cleanup_game(game);
	return (0);
}
