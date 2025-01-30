/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 16:22:00 by jcohen           ###   ########.fr       */
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
			WINDOW_HEIGHT, WINDOW_NAME);
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

static void	init_game_state(t_game *game)
{
	game->state.is_running = 1;
	game->state.window_focused = 1;
	game->state.mouse_captured = 0;
	game->input.mouse_sensitivity = MOUSE_SENSITIVITY;
	game->input.last_mouse_x = get_mouse_center_x();
	game->input.last_mouse_y = get_mouse_center_y();
	game->state.last_frame = get_time();
	game->state.delta_time = 0.0;
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
	init_game_state(game);
	setup_window_hooks(game);
	return (1);
}
