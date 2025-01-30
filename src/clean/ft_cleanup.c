/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:26:52 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 14:45:22 by jcohen           ###   ########.fr       */
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
		free(grid[i++]);
	free(grid);
}

void	free_texture_paths(t_map_data *map)
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

void	free_texture_images(t_map_data *map, void *mlx)
{
	if (!map || !mlx)
		return ;
	if (map->north.img)
		mlx_destroy_image(mlx, map->north.img);
	if (map->south.img)
		mlx_destroy_image(mlx, map->south.img);
	if (map->east.img)
		mlx_destroy_image(mlx, map->east.img);
	if (map->west.img)
		mlx_destroy_image(mlx, map->west.img);
}

void	clean_map_data(t_map_data *map, void *mlx)
{
	if (!map)
		return ;
	free_grid(map->grid, map->height);
	free_grid(map->flood_grid, map->height);
	free_texture_paths(map);
	free_texture_images(map, mlx);
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->renderer.frame.img)
		mlx_destroy_image(game->renderer.mlx, game->renderer.frame.img);
	if (game->renderer.minimap.img)
		mlx_destroy_image(game->renderer.mlx, game->renderer.minimap.img);
	if (game->renderer.win)
		mlx_destroy_window(game->renderer.mlx, game->renderer.win);
	if (game->map_data)
		clean_map_data(game->map_data, game->renderer.mlx);
	if (game->renderer.mlx)
	{
		mlx_destroy_display(game->renderer.mlx);
		free(game->renderer.mlx);
	}
	free(game);
}
