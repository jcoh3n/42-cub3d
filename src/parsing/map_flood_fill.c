/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:24 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:25:37 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_within_bounds(int x, int y, t_dims dims)
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
	if (!map || !is_within_bounds(x, y, dims))
		return (1);
	if (is_wall_or_visited(map[y][x]))
		return (1);
	if (is_outside_map(map[y][x]))
		return (0);
	map[y][x] = 'F';
	if (!flood_fill(map, x + 1, y, dims) || !flood_fill(map, x - 1, y, dims)
		|| !flood_fill(map, x, y + 1, dims) || !flood_fill(map, x, y - 1, dims))
		return (0);
	return (1);
}
