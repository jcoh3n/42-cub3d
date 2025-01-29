/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:26:52 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/29 15:39:53 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_map_data *map)
{
	if (!map)
		return ;
	if (map->north.path)
		free(map->north.path);
	if (map->south.path)
		free(map->south.path);
	if (map->east.path)
		free(map->east.path);
	if (map->west.path)
		free(map->west.path);
}

void	free_map(t_map_data *map)
{
	if (!map)
		return ;
	if (map->grid)
	{
		int	i = 0;
		while (i < map->height)
			free(map->grid[i++]);
		free(map->grid);
	}
	if (map->flood_grid)
	{
		int	i = 0;
		while (i < map->height)
			free(map->flood_grid[i++]);
		free(map->flood_grid);
	}
	free_textures(map);
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;

	// Cleanup renderer
	if (game->renderer.frame.img)
		mlx_destroy_image(game->renderer.mlx, game->renderer.frame.img);
	if (game->renderer.minimap.img)
		mlx_destroy_image(game->renderer.mlx, game->renderer.minimap.img);
	if (game->renderer.win)
		mlx_destroy_window(game->renderer.mlx, game->renderer.win);
	if (game->renderer.mlx)
	{
		mlx_destroy_display(game->renderer.mlx);
		free(game->renderer.mlx);
	}

	// Cleanup map data
	if (game->map_data)
	{
		if (game->map_data->grid)
			free_map_grid(game->map_data->grid);
		if (game->map_data->flood_grid)
			free_map_grid(game->map_data->flood_grid);
		
		// Cleanup textures
		if (game->map_data->north.img)
			mlx_destroy_image(game->renderer.mlx, game->map_data->north.img);
		if (game->map_data->south.img)
			mlx_destroy_image(game->renderer.mlx, game->map_data->south.img);
		if (game->map_data->east.img)
			mlx_destroy_image(game->renderer.mlx, game->map_data->east.img);
		if (game->map_data->west.img)
			mlx_destroy_image(game->renderer.mlx, game->map_data->west.img);
		
		free(game->map_data);
	}

	free(game);
}
