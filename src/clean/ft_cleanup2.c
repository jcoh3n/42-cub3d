/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:17:19 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:25:26 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_textures(t_game *game)
{
	if (game->map_data->north.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->north.img);
		game->map_data->north.img = NULL;
		game->map_data->north.addr = NULL;
	}
	if (game->map_data->south.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->south.img);
		game->map_data->south.img = NULL;
		game->map_data->south.addr = NULL;
	}
	if (game->map_data->west.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->west.img);
		game->map_data->west.img = NULL;
		game->map_data->west.addr = NULL;
	}
	if (game->map_data->east.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->east.img);
		game->map_data->east.img = NULL;
		game->map_data->east.addr = NULL;
	}
}

void	free_temp_map(char **temp_map)
{
	int	i;

	i = 0;
	while (temp_map[i])
		free(temp_map[i++]);
	free(temp_map);
}

void	free_map_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

void	free_flood_grid(t_map_data *map)
{
	if (map && map->flood_grid)
	{
		free_map_grid(map->flood_grid);
		map->flood_grid = NULL;
	}
}
