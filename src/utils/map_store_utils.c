/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:35 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/17 13:12:01 by j                ###   ########.fr       */
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

static char	**allocate_new_grid(t_map_data *map, char *new_line)
{
	char	**new_grid;

	new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
	{
		free(new_line);
		error_exit(ERR_MALLOC);
	}
	ft_memset(new_grid, 0, sizeof(char *) * (map->height + 2));
	return (new_grid);
}

static void	copy_old_grid(t_map_data *map, char **new_grid)
{
	int	i;

	i = -1;
	while (++i < map->height)
	{
		new_grid[i] = ft_strdup(map->grid[i]);
		if (!new_grid[i])
		{
			free_2d_array(new_grid, i);
			error_exit(ERR_MALLOC);
		}
	}
}

static char	**create_new_grid(t_map_data *map, char *new_line)
{
	char	**new_grid;

	new_grid = allocate_new_grid(map, new_line);
	copy_old_grid(map, new_grid);
	new_grid[map->height] = new_line;
	new_grid[map->height + 1] = NULL;
	return (new_grid);
}

void	update_map_grid(t_map_data *map, char *new_line)
{
	char	**new_grid;

	if (!map || !new_line)
		return ;
	new_grid = create_new_grid(map, new_line);
	free_old_grid(map);
	map->grid = new_grid;
	map->height++;
}
