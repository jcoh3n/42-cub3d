/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:26 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:04:36 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	validate_map(t_map_data *map)
{
	t_dims	dims;

	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		error_exit(ERR_MAP_ORDER);
	if (map->player_x < 0 || map->player_x >= map->width || map->player_y < 0
		|| map->player_y >= map->height)
		error_exit(ERR_PLAYER_POS);
	map->flood_grid = create_temp_map(map);
	dims.width = map->width;
	dims.height = map->height;
	if (!flood_fill(map->flood_grid, (int)map->player_x, (int)map->player_y,
			dims))
	{
		free_flood_grid(map);
		error_exit(ERR_MAP_WALLS);
	}
	if (!check_map_chars(map))
	{
		free_flood_grid(map);
		error_exit(ERR_MAP_CHARS);
	}
	if (!check_player(map))
	{
		free_flood_grid(map);
		error_exit(ERR_PLAYER_MULTIPLE);
	}
	if (!check_map_consistency(map))
	{
		free_flood_grid(map);
		error_exit(ERR_MAP_WALLS);
	}
	// Keep flood_grid for minimap rendering
}
