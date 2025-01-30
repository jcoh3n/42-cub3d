/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:21:21 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 16:21:28 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture_properties(t_texture *texture, void *img, int width,
		int height)
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	texture->img = img;
	texture->addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length,
			&endian);
	texture->width = width;
	texture->height = height;
	texture->line_length = line_length;
	texture->bits_per_pixel = bits_per_pixel;
	texture->endian = endian;
}

static int	load_north_south_textures(t_game *game)
{
	int	width;
	int	height;

	game->map_data->north.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->north.path, &width, &height);
	if (!game->map_data->north.img)
		return (0);
	init_texture_properties(&game->map_data->north, game->map_data->north.img,
		width, height);
	game->map_data->south.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->south.path, &width, &height);
	if (!game->map_data->south.img)
		return (0);
	init_texture_properties(&game->map_data->south, game->map_data->south.img,
		width, height);
	return (1);
}

static int	load_east_west_textures(t_game *game)
{
	int	width;
	int	height;

	game->map_data->west.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->west.path, &width, &height);
	if (!game->map_data->west.img)
		return (0);
	init_texture_properties(&game->map_data->west, game->map_data->west.img,
		width, height);
	game->map_data->east.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->east.path, &width, &height);
	if (!game->map_data->east.img)
		return (0);
	init_texture_properties(&game->map_data->east, game->map_data->east.img,
		width, height);
	return (1);
}

int	init_textures(t_game *game)
{
	if (!load_north_south_textures(game))
		return (0);
	if (!load_east_west_textures(game))
		return (0);
	return (1);
}
