/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:15:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/28 17:09:10 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_window_close(t_game *game)
{
	game->is_running = 0;
	mlx_loop_end(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);  // Force exit since the window isn't closing properly
	return (0);
}

int	handle_window_focus(int focused, t_game *game)
{
	game->window_focused = focused;
	if (!focused && game->mouse_captured)
		toggle_mouse_capture(game);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		handle_window_close(game);
		return (1);  // Return 1 to indicate the event was handled
	}
	else if (keycode == KEY_W)
		game->player.move_forward = 1;
	else if (keycode == KEY_S)
		game->player.move_backward = 1;
	else if (keycode == KEY_A)
		game->player.move_left = 1;
	else if (keycode == KEY_D)
		game->player.move_right = 1;
	else if (keycode == KEY_LEFT && !game->mouse_captured)
		game->player.rotate_left = 1;
	else if (keycode == KEY_RIGHT && !game->mouse_captured)
		game->player.rotate_right = 1;
	else if (keycode == MOUSE_CAPTURE_KEY)
		toggle_mouse_capture(game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	else if (keycode == KEY_S)
		game->player.move_backward = 0;
	else if (keycode == KEY_A)
		game->player.move_left = 0;
	else if (keycode == KEY_D)
		game->player.move_right = 0;
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 0;
	return (0);
}

void	setup_window_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, handle_window_close, game);
	mlx_hook(game->win, 9, 1L << 21, handle_window_focus, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse_move, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
