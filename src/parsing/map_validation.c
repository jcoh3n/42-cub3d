/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:26 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 01:17:27 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**copy_map_grid(t_map *map)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			error_exit(ERR_MALLOC);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_map_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

int	validate_map(t_map *map)
{
	char	**temp_map;
	t_dims	dims;
	int		valid;

	if (!check_map_consistency(map))
		return (0);
	dims.width = map->width;
	dims.height = map->height;
	temp_map = copy_map_grid(map);
	valid = flood_fill(temp_map, (int)map->player_x, (int)map->player_y, dims);
	free_map_grid(temp_map);
	if (!valid)
		error_exit(ERR_MAP_WALLS);
	return (1);
}

int	check_player_position(t_map *map, char **new_grid)
{
	int	i;
	int	j;

	i = 0;
	while (new_grid[i])
	{
		j = 0;
		while (new_grid[i][j])
		{
			if (ft_strchr("NSEW", new_grid[i][j]))
			{
				if (map->player_dir)
					return (0);
				map->player_dir = new_grid[i][j];
				map->player_x = j + 0.5;
				map->player_y = i + 0.5;
			}
			j++;
		}
		i++;
	}
	return (1);
}
