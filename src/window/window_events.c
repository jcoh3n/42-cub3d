/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:15:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:13:03 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_window_close(t_game *game)
{
	game->state.is_running = 0;
	mlx_loop_end(game->renderer.mlx);
	cleanup_game(game);
	exit(0);
	return (0);
}

int	handle_window_focus(int focused, t_game *game)
{
	game->state.window_focused = focused;
	if (!focused && game->state.mouse_captured)
		toggle_mouse_capture(game);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		handle_window_close(game);
		return (1);
	}
	else if (keycode == KEY_W)
		game->input.move_forward = 1;
	else if (keycode == KEY_S)
		game->input.move_backward = 1;
	else if (keycode == KEY_A)
		game->input.move_left = 1;
	else if (keycode == KEY_D)
		game->input.move_right = 1;
	else if (keycode == KEY_LEFT && !game->state.mouse_captured)
		game->input.rotate_left = 1;
	else if (keycode == KEY_RIGHT && !game->state.mouse_captured)
		game->input.rotate_right = 1;
	else if (keycode == KEY_M)
		toggle_mouse_capture(game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.move_forward = 0;
	else if (keycode == KEY_S)
		game->input.move_backward = 0;
	else if (keycode == KEY_A)
		game->input.move_left = 0;
	else if (keycode == KEY_D)
		game->input.move_right = 0;
	else if (keycode == KEY_LEFT)
		game->input.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		game->input.rotate_right = 0;
	return (0);
}

void	setup_window_hooks(t_game *game)
{
	mlx_hook(game->renderer.win, 17, 1L << 17, handle_window_close, game);
	mlx_hook(game->renderer.win, 9, 1L << 21, handle_window_focus, game);
	mlx_hook(game->renderer.win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->renderer.win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->renderer.win, 6, 1L << 6, handle_mouse_move, game);
}
