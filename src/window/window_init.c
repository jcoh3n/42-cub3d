/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/29 16:07:14 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_graphics_context(t_game *game)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game->renderer.mlx, &screen_width, &screen_height);
	if (WINDOW_WIDTH > screen_width || WINDOW_HEIGHT > screen_height)
		return (0);
	game->renderer.win = mlx_new_window(game->renderer.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	if (!game->renderer.win)
		return (0);
	return (1);
}

static int	init_frame_buffer(t_game *game)
{
	game->renderer.frame.img = mlx_new_image(game->renderer.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!game->renderer.frame.img)
		return (0);
	game->renderer.frame.addr = mlx_get_data_addr(game->renderer.frame.img,
			&game->renderer.frame.bits_per_pixel,
			&game->renderer.frame.line_length, &game->renderer.frame.endian);
	if (!game->renderer.frame.addr)
	{
		mlx_destroy_image(game->renderer.mlx, game->renderer.frame.img);
		return (0);
	}
	game->renderer.frame.width = WINDOW_WIDTH;
	game->renderer.frame.height = WINDOW_HEIGHT;
	return (1);
}

static int	init_textures(t_game *game)
{
	int	width;
	int	height;
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	// Load North texture
	game->map_data->north.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->north.path, &width, &height);
	if (!game->map_data->north.img)
		return (0);
	game->map_data->north.addr = mlx_get_data_addr(game->map_data->north.img,
			&bits_per_pixel, &line_length, &endian);
	game->map_data->north.width = width;
	game->map_data->north.height = height;
	game->map_data->north.line_length = line_length;
	game->map_data->north.bits_per_pixel = bits_per_pixel;
	game->map_data->north.endian = endian;
	// Load South texture
	game->map_data->south.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->south.path, &width, &height);
	if (!game->map_data->south.img)
		return (0);
	game->map_data->south.addr = mlx_get_data_addr(game->map_data->south.img,
			&bits_per_pixel, &line_length, &endian);
	game->map_data->south.width = width;
	game->map_data->south.height = height;
	game->map_data->south.line_length = line_length;
	game->map_data->south.bits_per_pixel = bits_per_pixel;
	game->map_data->south.endian = endian;
	// Load West texture
	game->map_data->west.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->west.path, &width, &height);
	if (!game->map_data->west.img)
		return (0);
	game->map_data->west.addr = mlx_get_data_addr(game->map_data->west.img,
			&bits_per_pixel, &line_length, &endian);
	game->map_data->west.width = width;
	game->map_data->west.height = height;
	game->map_data->west.line_length = line_length;
	game->map_data->west.bits_per_pixel = bits_per_pixel;
	game->map_data->west.endian = endian;
	// Load East texture
	game->map_data->east.img = mlx_xpm_file_to_image(game->renderer.mlx,
			game->map_data->east.path, &width, &height);
	if (!game->map_data->east.img)
		return (0);
	game->map_data->east.addr = mlx_get_data_addr(game->map_data->east.img,
			&bits_per_pixel, &line_length, &endian);
	game->map_data->east.width = width;
	game->map_data->east.height = height;
	game->map_data->east.line_length = line_length;
	game->map_data->east.bits_per_pixel = bits_per_pixel;
	game->map_data->east.endian = endian;
	return (1);
}

void	cleanup_textures(t_game *game)
{
	// North texture
	if (game->map_data->north.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->north.img);
		game->map_data->north.img = NULL;
		game->map_data->north.addr = NULL;
	}
	// South texture
	if (game->map_data->south.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->south.img);
		game->map_data->south.img = NULL;
		game->map_data->south.addr = NULL;
	}
	// West texture
	if (game->map_data->west.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->west.img);
		game->map_data->west.img = NULL;
		game->map_data->west.addr = NULL;
	}
	// East texture
	if (game->map_data->east.img)
	{
		mlx_destroy_image(game->renderer.mlx, game->map_data->east.img);
		game->map_data->east.img = NULL;
		game->map_data->east.addr = NULL;
	}
}

int	init_window(t_game *game)
{
	if (!init_graphics_context(game))
	{
		if (game->renderer.win)
			mlx_destroy_window(game->renderer.mlx, game->renderer.win);
		error_exit(ERR_WINDOW_INIT);
	}
	if (!init_frame_buffer(game))
	{
		if (game->renderer.win)
			mlx_destroy_window(game->renderer.mlx, game->renderer.win);
		error_exit(ERR_IMAGE_INIT);
	}
	if (!init_textures(game))
	{
		if (game->renderer.win)
			mlx_destroy_window(game->renderer.mlx, game->renderer.win);
		error_exit(ERR_TEXTURE_ACCESS);
	}
	// Initialize game state
	game->state.is_running = 1;
	game->state.window_focused = 1;
	game->state.mouse_captured = 0;
	game->input.last_mouse_x = MOUSE_CENTER_X;
	game->input.last_mouse_y = MOUSE_CENTER_Y;
	// Set up event handlers
	setup_window_hooks(game);
	// Initialize timing
	game->state.last_frame = get_time();
	game->state.delta_time = 0.0;
	return (1);
}
