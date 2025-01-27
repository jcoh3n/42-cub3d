/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:26 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/27 17:04:14 by jcohen           ###   ########.fr       */
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

void	validate_map(t_map *map)
{
	t_dims	dims;

	if (!map->grid)
		error_exit(ERR_MAP_ORDER);
	map->flood_grid = create_temp_map(map);
	dims.width = map->width;
	dims.height = map->height;
	if (!flood_fill(map->flood_grid, (int)map->player_x, (int)map->player_y,
			dims))
		error_exit(ERR_MAP_WALLS);
	check_map_consistency(map);
}
