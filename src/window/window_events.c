/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:15:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/27 16:53:56 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_window_close(t_game *game)
{
	game->is_running = 0;
	mlx_loop_end(game->mlx);
	return (0);
}

int	handle_window_focus(int focused, t_game *game)
{
	game->window_focused = focused;
	return (0);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	static int	last_update = 0;
	int			current_time;
	double		dx;

	(void)y;
	if (!game->player.mouse_enabled || !game->window_focused)
		return (0);
	// Limiter la fréquence de mise à jour de la souris
	current_time = get_time() * 1000;
	if (current_time - last_update < 16) // ~60 FPS
		return (0);
	last_update = current_time;
	// Calculer la rotation de manière plus précise
	dx = (x - WINDOW_WIDTH / 2) * MOUSE_SENSITIVITY;
	if (fabs(dx) > 0.0001) // Éviter les micro-mouvements
	{
		rotate_player(game, dx);
		mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT
			/ 2);
	}
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (handle_window_close(game));
	else if (keycode == KEY_W)
		game->player.move_forward = 1;
	else if (keycode == KEY_S)
		game->player.move_backward = 1;
	else if (keycode == KEY_A)
		game->player.move_left = 1;
	else if (keycode == KEY_D)
		game->player.move_right = 1;
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 1;
	else if (keycode == KEY_M && game->window_focused)
	{
		game->player.mouse_enabled = !game->player.mouse_enabled;
		if (game->player.mouse_enabled)
		{
			mlx_mouse_hide(game->mlx, game->win);
			mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT
				/ 2);
		}
		else
			mlx_mouse_show(game->mlx, game->win);
	}
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
