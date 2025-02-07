/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:24 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:09:23 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_within_bounds(int x, int y, t_dims dims)
{
	return (x >= 0 && x < dims.width && y >= 0 && y < dims.height);
}

static int	is_wall_or_visited(char c)
{
	return (c == '1' || c == 'F');
}

static int	is_outside_map(char c)
{
	return (c == ' ' || c == '\0');
}

int	flood_fill(char **map, int x, int y, t_dims dims)
{
	if (!map || !is_within_bounds(x, y, dims))
		return (1);
	if (is_wall_or_visited(map[y][x]))
		return (1);
	if (is_outside_map(map[y][x]))
		return (0);
	map[y][x] = 'F';
	if (!flood_fill(map, x + 1, y, dims) || !flood_fill(map, x - 1, y, dims)
		|| !flood_fill(map, x, y + 1, dims) || !flood_fill(map, x, y - 1, dims))
		return (0);
	return (1);
}

static void	cleanup_temp_map(char **temp_map, int height)
{
	int	i;

	if (!temp_map)
		return ;
	i = 0;
	while (i < height)
	{
		if (temp_map[i])
		{
			free(temp_map[i]);
			temp_map[i] = NULL;
		}
		i++;
	}
	free(temp_map);
}

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
			cleanup_temp_map(temp_map, i);
			error_exit(ERR_MALLOC);
		}
		temp_map[i] = ft_strdup(map->grid[i]);
		if (!temp_map[i])
		{
			cleanup_temp_map(temp_map, i);
			error_exit(ERR_MALLOC);
		}
	}
	temp_map[i] = NULL;
	return (temp_map);
}
