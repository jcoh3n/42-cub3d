/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_consistency.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:22 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:26:54 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_edges(t_map_data *map)
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
				error_exit(ERR_MAP_WALLS);
			j++;
		}
		i++;
	}
}

void	check_map_consistency(t_map_data *map)
{
	check_map_chars(map);
	check_map_edges(map);
	check_player(map);
}
