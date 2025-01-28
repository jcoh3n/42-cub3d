/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:22 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/28 21:57:22 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_position(t_map *map, int i, int j)
{
	int	len_above;
	int	len_below;

	// If it's a wall or space, it's always valid
	if (map->grid[i][j] == '1' || map->grid[i][j] == ' ')
		return (1);

	// For non-wall positions (0 or player), check if they're enclosed
	// Check if position is at the edge
	if (i <= 0 || i >= map->height - 1)
		return (0);

	len_above = ft_strlen(map->grid[i - 1]);
	len_below = ft_strlen(map->grid[i + 1]);

	// Check if position is beyond any surrounding line's length
	if (j >= len_above || j >= len_below)
		return (0);

	// Check surrounding positions
	if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' ')
		return (0);

	// Check left and right
	if (j == 0 || j == (int)ft_strlen(map->grid[i]) - 1)
		return (0);
	if (map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
		return (0);

	return (1);
}

static void	check_map_edges(t_map *map)
{
	int	i;
	int	j;
	int	len;

	// Check all positions
	for (i = 0; i < map->height; i++)
	{
		len = ft_strlen(map->grid[i]);
		for (j = 0; j < len; j++)
		{
			// Skip spaces
			if (map->grid[i][j] == ' ')
				continue;
			// If not a wall and not properly enclosed
			if (map->grid[i][j] != '1' && !is_valid_position(map, i, j))
				error_exit(ERR_MAP_WALLS);
		}
	}
}

static void	check_map_chars(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (map->grid[i][++j])
		{
			if (!is_map_char(map->grid[i][j]))
				error_exit(ERR_MAP_CHARS);
		}
	}
}

static void	check_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = -1;
	player_count = 0;
	while (++i < map->height)
	{
		j = -1;
		while (map->grid[i][++j])
		{
			if (ft_strchr(PLAYER_CHARS, map->grid[i][j]))
				player_count++;
		}
	}
	if (player_count == 0)
		error_exit(ERR_PLAYER_NONE);
	if (player_count > 1)
		error_exit(ERR_PLAYER_MULTIPLE);
}

void	check_map_consistency(t_map *map)
{
	check_map_chars(map);
	check_map_edges(map);
	check_player(map);
}

int	check_line_consistency(t_map *map, int i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (map->grid[i][j] != ' ' && map->grid[i][j] != '1')
		{
			if (!is_valid_position(map, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}
