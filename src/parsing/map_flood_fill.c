/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:24 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 00:28:14 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(char **map, int x, int y, t_dims dims)
{
	if (x < 0 || x >= dims.width || y < 0 || y >= dims.height)
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
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
