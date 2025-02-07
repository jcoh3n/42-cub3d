/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:26 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 20:00:38 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**create_temp_map(t_map_data *map)
{
	char	**temp_map;
	int		i;

	if (!map || !map->grid || map->height <= 0)
		error_exit(ERR_MAP_ORDER);
	temp_map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!temp_map)
		error_exit(ERR_MALLOC);
	ft_memset(temp_map, 0, sizeof(char *) * (map->height + 1));
	i = -1;
	while (++i < map->height)
	{
		if (!map->grid[i])
		{
			free_2d_array(temp_map, i);
			error_exit(ERR_MALLOC);
		}
		temp_map[i] = ft_strdup(map->grid[i]);
		if (!temp_map[i])
		{
			free_2d_array(temp_map, i);
			error_exit(ERR_MALLOC);
		}
	}
	return (temp_map[i] = NULL, temp_map);
}

static void	check_map_all(t_map_data *map)
{
	int	player_check;

	if (!check_map_chars(map))
		error_exit(ERR_MAP_CHARS);
	if (!check_map_consistency(map))
		error_exit(ERR_MAP_WALLS);
	player_check = check_player(map);
	if (player_check == -1)
		error_exit(ERR_NO_PLAYER);
	if (player_check == 0)
		error_exit(ERR_PLAYER_MULTIPLE);
}

void	validate_map(t_map_data *map)
{
	t_dims	dims;

	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		error_exit(ERR_MAP_ORDER);
	check_map_all(map);
	map->flood_grid = create_temp_map(map);
	dims.width = map->width;
	dims.height = map->height;
	if (!flood_fill(map->flood_grid, (int)map->player_x, (int)map->player_y,
			dims))
	{
		free_2d_array(map->flood_grid, map->height);
		map->flood_grid = NULL;
		error_exit(ERR_MAP_WALLS);
	}
}
