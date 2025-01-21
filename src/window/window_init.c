/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 01:00:39 by jcohen           ###   ########.fr       */
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

static void setup_input_handlers(t_game *game)
{
	mlx_hook(game->win, 2, 1L<<0, handle_player_keypress, game);
	mlx_hook(game->win, 3, 1L<<1, handle_player_keyrelease, game);
	mlx_hook(game->win, 17, 0, handle_window_close, game);
	mlx_hook(game->win, 9, 1L<<21, handle_window_focus, game);
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
	game->is_running = 1;
	game->window_focused = 1;
	setup_input_handlers(game);
	init_player(game);
	return (1);
}
