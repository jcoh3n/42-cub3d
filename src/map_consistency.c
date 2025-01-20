/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:22 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 16:23:00 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_position(t_map *map, int i, int j)
{
	// Check if position is at map borders
	if (i == 0 || i == map->height - 1)
		return (0);
	
	// Check if position is at line edges
	if (j == 0 || j >= (int)ft_strlen(map->grid[i]) - 1)
		return (0);
	
	// Check if any surrounding position is a space
	if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' ' ||
		map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
		return (0);

	return (1);
}

int	check_map_consistency(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		if (!map->grid[i][0])
			error_exit("Empty line in map");
		j = 0;
		while (map->grid[i][j])
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
				player_count++;
			if (!is_map_char(map->grid[i][j]))
				error_exit("Invalid character in map");
			if (map->grid[i][j] != '1' && map->grid[i][j] != ' ' && !is_valid_position(map, i, j))
				error_exit("Map is not properly enclosed");
			j++;
		}
		i++;
	}
	if (player_count == 0)
		error_exit("No player position found in map");
	if (player_count > 1)
		error_exit("Multiple player positions found in map");
	return (1);
}

int	is_space_valid(t_map *map, int i, int j)
{
	// Spaces at map borders are valid
	if (i == 0 || i == map->height - 1 || j == 0 || j >= (int)ft_strlen(map->grid[i]) - 1)
		return (1);
	
	// Check if space is adjacent to a walkable area (non-wall, non-space)
	if (map->grid[i - 1][j] != '1' && map->grid[i - 1][j] != ' ')
		return (0);
	if (map->grid[i + 1][j] != '1' && map->grid[i + 1][j] != ' ')
		return (0);
	if (map->grid[i][j - 1] != '1' && map->grid[i][j - 1] != ' ')
		return (0);
	if (map->grid[i][j + 1] != '1' && map->grid[i][j + 1] != ' ')
		return (0);

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
			// For non-wall characters, check if they're properly enclosed
			if (!is_valid_position(map, i, j))
				return (0);
		}
		else if (map->grid[i][j] == ' ')
		{
			// For spaces, ensure they don't create gaps in walls
			if (!is_space_valid(map, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}



