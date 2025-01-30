/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:17:19 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 16:17:24 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_textures(t_game *game)
{
	if (game->map_data->north.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->north.img);
		game->map_data->north.img = NULL;
		game->map_data->north.addr = NULL;
	}
	if (game->map_data->south.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->south.img);
		game->map_data->south.img = NULL;
		game->map_data->south.addr = NULL;
	}
	if (game->map_data->west.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->west.img);
		game->map_data->west.img = NULL;
		game->map_data->west.addr = NULL;
	}
	if (game->map_data->east.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->east.img);
		game->map_data->east.img = NULL;
		game->map_data->east.addr = NULL;
	}
}
