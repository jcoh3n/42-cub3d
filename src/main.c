/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 16:06:12 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(char *message)
{
	printf("Error\n%s\n", message);
	exit(1);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
			free(map->grid[i++]);
		free(map->grid);
	}
	if (map->north.path)
		free(map->north.path);
	if (map->south.path)
		free(map->south.path);
	if (map->east.path)
		free(map->east.path);
	if (map->west.path)
		free(map->west.path);
	free(map);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		error_exit("Memory allocation failed");
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
		error_exit("Memory allocation failed");
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("MLX initialization failed");
	game->win = NULL;
	game->map = init_map();
	return (game);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
		free_map(game->map);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
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
	
	// Rest of the game initialization will go here
	
	cleanup_game(game);
	return (0);
}
