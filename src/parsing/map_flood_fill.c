/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:24 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/25 00:44:59 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_position(int x, int y, t_dims dims)
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
	if (!is_valid_position(x, y, dims))
		return (0);
	if (is_outside_map(map[y][x]))
		return (1);
	if (is_wall_or_visited(map[y][x]))
		return (1);
	map[y][x] = 'F';
	return (flood_fill(map, x + 1, y, dims) && flood_fill(map, x - 1, y, dims)
		&& flood_fill(map, x, y + 1, dims) && flood_fill(map, x, y - 1, dims));
}

char	**create_temp_map(t_map *map)
{
	char	**temp_map;
	int		i;

	temp_map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!temp_map)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < map->height)
	{
		temp_map[i] = ft_strdup(map->grid[i]);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			error_exit(ERR_MALLOC);
		}
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

void	free_temp_map(char **temp_map)
{
	int	i;

	i = 0;
	while (temp_map[i])
		free(temp_map[i++]);
	free(temp_map);
}
