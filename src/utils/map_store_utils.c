/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:35 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:21:08 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_old_grid(t_map_data *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
		free(map->grid[i++]);
	free(map->grid);
}

void	update_map_grid(t_map_data *map, char *new_line)
{
	char	**new_grid;
	int		i;

	new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = ft_strdup(map->grid[i]);
		if (!new_grid[i])
			error_exit(ERR_MALLOC);
		i++;
	}
	new_grid[i] = new_line;
	new_grid[i + 1] = NULL;
	free_old_grid(map);
	map->grid = new_grid;
	map->height++;
}
