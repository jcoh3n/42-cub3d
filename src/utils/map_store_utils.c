/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:35 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:09:23 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_old_grid(t_map_data *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

static void	cleanup_new_grid(char **new_grid, int height)
{
	int	i;

	if (!new_grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (new_grid[i])
		{
			free(new_grid[i]);
			new_grid[i] = NULL;
		}
		i++;
	}
	free(new_grid);
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
			cleanup_new_grid(new_grid, i);
			error_exit(ERR_MALLOC);
		}
	}
	new_grid[i] = new_line;
	new_grid[i + 1] = NULL;
	free_old_grid(map);
	map->grid = new_grid;
	map->height++;
}
