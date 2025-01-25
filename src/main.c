/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/25 17:38:56 by jcohen           ###   ########.fr       */
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

void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
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
	game->map = NULL;
	game->map_data = init_map();
	game->minimap.img = NULL;
	game->minimap.addr = NULL;
	game->minimap.width = 0;
	game->minimap.height = 0;
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
	t_game		*game;
	int			fd;
	struct stat	path_stat;

	if (argc != 2)
		error_exit(ERR_USAGE);
	if (!ft_strendswith(argv[1], ".cub"))
		error_exit(ERR_FILE_EXT);
	stat(argv[1], &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		error_exit(ERR_IS_DIR);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit(ERR_FILE);
	close(fd);
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
