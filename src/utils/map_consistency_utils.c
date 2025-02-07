/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:39 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:31:32 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_position(t_map_data *map, int i, int j)
{
	int	len_above;
	int	len_below;
	int	curr_len;

	if (map->grid[i][j] == '1' || map->grid[i][j] == ' ')
		return (1);
	if (i <= 0 || i >= map->height - 1)
		return (0);
	len_above = ft_strlen(map->grid[i - 1]);
	len_below = ft_strlen(map->grid[i + 1]);
	curr_len = ft_strlen(map->grid[i]);
	if (j >= len_above || j >= len_below || j >= curr_len)
		return (0);
	if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' ')
		return (0);
	if (j == 0 || j == curr_len - 1)
		return (0);
	if (map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
		return (0);
	if (j >= len_above - 1 || j >= len_below - 1)
		return (0);
	if (map->grid[i - 1][j + 1] == ' ' || map->grid[i + 1][j + 1] == ' '
		|| map->grid[i - 1][j - 1] == ' ' || map->grid[i + 1][j - 1] == ' ')
		return (0);
	return (1);
}

int	check_map_chars(t_map_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (!ft_strchr(VALID_MAP_CHARS, map->grid[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player(t_map_data *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (ft_strchr(PLAYER_CHARS, map->grid[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (-1); // No player found
	if (player_count > 1)
		return (0); // Multiple players found
	return (1);     // Exactly one player found
}

int	check_line_consistency(t_map_data *map, int i, int len)
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
