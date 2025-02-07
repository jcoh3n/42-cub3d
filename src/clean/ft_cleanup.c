/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:26:52 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:12:23 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (grid[i])
		{
			free(grid[i]);
			grid[i] = NULL;
		}
		i++;
	}
	free(grid);
}

void	free_texture_paths(t_map_data *map)
{
	if (!map)
		return ;
	if (map->north.path)
	{
		free(map->north.path);
		map->north.path = NULL;
	}
	if (map->south.path)
	{
		free(map->south.path);
		map->south.path = NULL;
	}
	if (map->east.path)
	{
		free(map->east.path);
		map->east.path = NULL;
	}
	if (map->west.path)
	{
		free(map->west.path);
		map->west.path = NULL;
	}
}

void	free_texture_images(t_map_data *map, void *mlx)
{
	if (!map || !mlx)
		return ;
	if (map->north.img)
	{
		mlx_destroy_image(mlx, map->north.img);
		map->north.img = NULL;
	}
	if (map->south.img)
	{
		mlx_destroy_image(mlx, map->south.img);
		map->south.img = NULL;
	}
	if (map->east.img)
	{
		mlx_destroy_image(mlx, map->east.img);
		map->east.img = NULL;
	}
	if (map->west.img)
	{
		mlx_destroy_image(mlx, map->west.img);
		map->west.img = NULL;
	}
}

void	free_map_lines(t_map_data *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		i++;
	}
}

void	clean_map_data(t_map_data *map, void *mlx)
{
	if (!map)
		return ;
	if (map->grid)
	{
		free_map_lines(map);
		free(map->grid);
		map->grid = NULL;
	}
	if (map->flood_grid)
	{
		free_grid(map->flood_grid, map->height);
		map->flood_grid = NULL;
	}
	free_texture_paths(map);
	free_texture_images(map, mlx);
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->renderer.frame.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->renderer.frame.img);
		game->renderer.frame.img = NULL;
	}
	if (game->renderer.minimap.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->renderer.minimap.img);
		game->renderer.minimap.img = NULL;
	}
	if (game->renderer.win)
	{
		mlx_destroy_window(game->renderer.mlx, game->renderer.win);
		game->renderer.win = NULL;
	}
	if (game->map_data)
	{
		clean_map_data(game->map_data, game->renderer.mlx);
		game->map_data = NULL;
	}
	if (game->renderer.mlx)
	{
		mlx_destroy_display(game->renderer.mlx);
		free(game->renderer.mlx);
		game->renderer.mlx = NULL;
	}
	free(game);
}
