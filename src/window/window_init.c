/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/28 11:26:54 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_graphics_context(t_game *game)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (WINDOW_WIDTH > screen_width || WINDOW_HEIGHT > screen_height)
		return (0);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (0);
	return (1);
}

static int	init_frame_buffer(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img.img)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		return (0);
	}
	game->img.width = WINDOW_WIDTH;
	game->img.height = WINDOW_HEIGHT;
	return (1);
}

static void	setup_input_handlers(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 0, handle_window_close, game);
	mlx_hook(game->win, 9, 1L << 21, handle_window_focus, game);
}

static int init_textures(t_game *game)
{
	int width;
	int height;
	int bits_per_pixel;
	int line_length;
	int endian;

	// Load North texture
	game->map_data->north.img = mlx_xpm_file_to_image(game->mlx, 
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
	game->map_data->south.img = mlx_xpm_file_to_image(game->mlx, 
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
	game->map_data->west.img = mlx_xpm_file_to_image(game->mlx, 
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
	game->map_data->east.img = mlx_xpm_file_to_image(game->mlx, 
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

void cleanup_textures(t_game *game)
{
	// North texture
	if (game->map_data->north.img)
	{
		mlx_destroy_image(game->mlx, game->map_data->north.img);
		game->map_data->north.img = NULL;
		game->map_data->north.addr = NULL;
	}
	
	// South texture
	if (game->map_data->south.img)
	{
		mlx_destroy_image(game->mlx, game->map_data->south.img);
		game->map_data->south.img = NULL;
		game->map_data->south.addr = NULL;
	}
	
	// West texture
	if (game->map_data->west.img)
	{
		mlx_destroy_image(game->mlx, game->map_data->west.img);
		game->map_data->west.img = NULL;
		game->map_data->west.addr = NULL;
	}
	
	// East texture
	if (game->map_data->east.img)
	{
		mlx_destroy_image(game->mlx, game->map_data->east.img);
		game->map_data->east.img = NULL;
		game->map_data->east.addr = NULL;
	}
}

int	init_window(t_game *game)
{
	if (!init_graphics_context(game))
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		error_exit(ERR_WINDOW_INIT);
	}
	if (!init_frame_buffer(game))
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		error_exit(ERR_IMAGE_INIT);
	}
	if (!init_textures(game))
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		error_exit(ERR_TEXTURE_ACCESS);
	}
	game->is_running = 1;
	game->window_focused = 1;
	setup_input_handlers(game);
	init_player(game);
	game->last_frame = (int)get_time();
	game->delta_time = 0.0;
	return (1);
}
