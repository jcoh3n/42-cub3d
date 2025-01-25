/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:15:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/25 16:22:57 by jcohen           ###   ########.fr       */
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

int	handle_player_keypress(int keycode, t_game *game)
{
	printf("Key pressed: %d\n", keycode);

	if (keycode == KEY_ESC)
	{
		printf("ESC pressed - exiting\n");
		game->is_running = 0;
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else if (keycode == KEY_W)
	{
		printf("W pressed - move forward\n");
		game->player.move_forward = 1;
	}
	else if (keycode == KEY_S)
	{
		printf("S pressed - move backward\n");
		game->player.move_backward = 1;
	}
	else if (keycode == KEY_A)
	{
		printf("A pressed - move left\n");
		game->player.move_left = 1;
	}
	else if (keycode == KEY_D)
	{
		printf("D pressed - move right\n");
		game->player.move_right = 1;
	}
	else if (keycode == KEY_LEFT)
	{
		printf("LEFT pressed - rotate left\n");
		game->player.rotate_left = 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		printf("RIGHT pressed - rotate right\n");
		game->player.rotate_right = 1;
	}
	return (0);
}

int	handle_player_keyrelease(int keycode, t_game *game)
{
	printf("Key released: %d\n", keycode);

	if (keycode == KEY_W)
	{
		printf("W released - stop moving forward\n");
		game->player.move_forward = 0;
	}
	else if (keycode == KEY_S)
	{
		printf("S released - stop moving backward\n");
		game->player.move_backward = 0;
	}
	else if (keycode == KEY_A)
	{
		printf("A released - stop moving left\n");
		game->player.move_left = 0;
	}
	else if (keycode == KEY_D)
	{
		printf("D released - stop moving right\n");
		game->player.move_right = 0;
	}
	else if (keycode == KEY_LEFT)
	{
		printf("LEFT released - stop rotating left\n");
		game->player.rotate_left = 0;
	}
	else if (keycode == KEY_RIGHT)
	{
		printf("RIGHT released - stop rotating right\n");
		game->player.rotate_right = 0;
	}
	return (0);
}

void	setup_window_hooks(t_game *game)
{
	// Window management hooks
	mlx_hook(game->win, 17, 0, handle_window_close, game);
	mlx_hook(game->win, 9, 1L << 21, handle_window_focus, game);

	// Keyboard input hooks - using X11 event codes
	mlx_hook(game->win, 2, 1L << 0, handle_player_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_player_keyrelease, game);

	// Game loop hook for continuous updates
	mlx_loop_hook(game->mlx, game_loop, game);
}
