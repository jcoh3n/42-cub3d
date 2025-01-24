/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:22 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/25 00:45:34 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_position(t_map *map, int i, int j)
{
	if (i <= 0 || i >= map->height - 1 || j <= 0
		|| j >= (int)ft_strlen(map->grid[i]) - 1)
		return (0);
	if (map->grid[i][j] != '0' && !ft_strchr(PLAYER_CHARS, map->grid[i][j]))
		return (1);
	return (map->grid[i - 1][j] && ft_strchr(VALID_MAP_CHARS, map->grid[i
			- 1][j]) && map->grid[i + 1][j] && ft_strchr(VALID_MAP_CHARS,
			map->grid[i + 1][j]) && map->grid[i][j - 1]
		&& ft_strchr(VALID_MAP_CHARS, map->grid[i][j - 1]) && map->grid[i][j
		+ 1] && ft_strchr(VALID_MAP_CHARS, map->grid[i][j + 1]));
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

static void	check_walls(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (map->grid[i][++j])
		{
			if (map->grid[i][j] != '1' && map->grid[i][j] != ' '
				&& !is_valid_position(map, i, j))
				error_exit(ERR_MAP_WALLS);
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
	check_walls(map);
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
