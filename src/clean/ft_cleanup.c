/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:26:52 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 19:27:26 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
		free_map(game->map);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
			free(map->grid[i++]);
		free(map->grid);
	}
	if (map->north.path)
		free(map->north.path);
	if (map->south.path)
		free(map->south.path);
	if (map->east.path)
		free(map->east.path);
	if (map->west.path)
		free(map->west.path);
	free(map);
}
