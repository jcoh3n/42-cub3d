/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:26 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:34:42 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_temp_map(char **temp_map, int height)
{
	int	i;

	if (!temp_map)
		return ;
	i = 0;
	while (i < height)
	{
		if (temp_map[i])
		{
			free(temp_map[i]);
			temp_map[i] = NULL;
		}
		i++;
	}
	free(temp_map);
}

char	**create_temp_map(t_map_data *map)
{
	char	**temp_map;
	int		i;

	if (!map || !map->grid || map->height <= 0)
		error_exit(ERR_MAP_ORDER);
	temp_map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!temp_map)
		error_exit(ERR_MALLOC);
	ft_memset(temp_map, 0, sizeof(char *) * (map->height + 1));
	i = -1;
	while (++i < map->height)
	{
		if (!map->grid[i])
		{
			cleanup_temp_map(temp_map, i);
			error_exit(ERR_MALLOC);
		}
		temp_map[i] = ft_strdup(map->grid[i]);
		if (!temp_map[i])
		{
			cleanup_temp_map(temp_map, i);
			error_exit(ERR_MALLOC);
		}
	}
	temp_map[i] = NULL;
	return (temp_map);
}

static void	check_map_all(t_map_data *map)
{
	int	player_check;

	// First check for valid characters
	if (!check_map_chars(map))
		error_exit(ERR_MAP_CHARS);
	// Then check map structure (walls and consistency)
	if (!check_map_consistency(map))
		error_exit(ERR_MAP_WALLS);
	// Finally check player existence and validity
	player_check = check_player(map);
	if (player_check == -1)
		error_exit(ERR_NO_PLAYER);
	if (player_check == 0)
		error_exit(ERR_PLAYER_MULTIPLE);
}

void	validate_map(t_map_data *map)
{
	t_dims	dims;

	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		error_exit(ERR_MAP_ORDER);
	// First check all basic map validations including player
	check_map_all(map);
	// Now we can safely do flood fill since we know we have a valid player
	map->flood_grid = create_temp_map(map);
	dims.width = map->width;
	dims.height = map->height;
	if (!flood_fill(map->flood_grid, (int)map->player_x, (int)map->player_y,
			dims))
	{
		free_flood_grid(map);
		error_exit(ERR_MAP_WALLS);
	}
}
