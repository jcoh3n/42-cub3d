/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:22 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 19:24:03 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_position(t_map *map, int i, int j)
{
	if (i == 0 || i == map->height - 1)
		return (0);
	if (j == 0 || j >= (int)ft_strlen(map->grid[i]) - 1)
		return (0);
	if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
		|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
		return (0);
	return (1);
}

static int	check_player_count(int player_count)
{
	if (player_count == 0)
		error_exit(ERR_PLAYER_NONE);
	if (player_count > 1)
		error_exit(ERR_PLAYER_MULTIPLE);
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
			error_exit(ERR_MAP_EMPTY);
		j = 0;
		while (map->grid[i][j])
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
				player_count++;
			if (!is_map_char(map->grid[i][j]))
				error_exit(ERR_MAP_CHARS);
			if (map->grid[i][j] != '1' && map->grid[i][j] != ' '
				&& !is_valid_position(map, i, j))
				error_exit(ERR_MAP_WALLS);
			j++;
		}
		i++;
	}
	return (check_player_count(player_count));
}

int	is_space_valid(t_map *map, int i, int j)
{
	if (i == 0 || i == map->height - 1 || j == 0
		|| j >= (int)ft_strlen(map->grid[i]) - 1)
		return (1);
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
			if (!is_valid_position(map, i, j))
				return (0);
		}
		else if (map->grid[i][j] == ' ')
		{
			if (!is_space_valid(map, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}
