/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:35 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:58:59 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_old_grid(t_map_data *map)
{
	if (!map || !map->grid)
		return ;
	free_2d_array(map->grid, map->height);
	map->grid = NULL;
}

void	update_map_grid(t_map_data *map, char *new_line)
{
	char	**new_grid;
	int		i;

	if (!map || !new_line)
		return ;
	new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
	{
		free(new_line);
		error_exit(ERR_MALLOC);
	}
	ft_memset(new_grid, 0, sizeof(char *) * (map->height + 2));
	i = -1;
	while (++i < map->height)
	{
		new_grid[i] = ft_strdup(map->grid[i]);
		if (!new_grid[i])
		{
			free(new_line);
			free_2d_array(new_grid, i);
			error_exit(ERR_MALLOC);
		}
	}
	new_grid[i] = new_line;
	new_grid[i + 1] = NULL;
	free_old_grid(map);
	map->grid = new_grid;
	map->height++;
}
