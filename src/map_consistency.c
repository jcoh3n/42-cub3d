/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:22 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 15:47:59 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_consistency(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < map->height)
	{
		if (!map->grid[i][0])
			error_exit(ERR_MAP_EMPTY_LINE);
		len = ft_strlen(map->grid[i]);
		if (map->grid[i][0] != WALL || map->grid[i][len - 1] != WALL)
			error_exit(ERR_MAP_WALLS);
		if (!check_line_consistency(map, i, len))
			return (0);
		i++;
	}
	return (1);
}

int	check_line_consistency(t_map *map, int i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (map->grid[i][j] != ' ' && map->grid[i][j] != '1')
		{
			if (i == 0 || i == map->height - 1)
				return (0);
			if (!check_surrounding_walls(map, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}

int	check_surrounding_walls(t_map *map, int i, int j)
{
	if (j == 0 || j == (int)ft_strlen(map->grid[i]) - 1)
		return (0);
	if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
		|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
		return (0);
	return (1);
}
