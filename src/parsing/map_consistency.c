/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:22 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:00:46 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_edges(t_map_data *map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		len = ft_strlen(map->grid[i]);
		while (j < len)
		{
			if (map->grid[i][j] != ' ' && map->grid[i][j] != '1'
				&& !is_valid_position(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_consistency(t_map_data *map)
{
	if (!check_map_chars(map))
		return (0);
	if (!check_map_edges(map))
		return (0);
	if (!check_player(map))
		return (0);
	return (1);
}
