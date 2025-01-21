/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:54:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 01:30:13 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	handle_movement_press(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player->move_forward = 1;
	else if (keycode == KEY_S)
		player->move_backward = 1;
	else if (keycode == KEY_A)
		player->move_left = 1;
	else if (keycode == KEY_D)
		player->move_right = 1;
}

static void	handle_rotation_press(int keycode, t_player *player)
{
	if (keycode == KEY_LEFT)
		player->rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		player->rotate_right = 1;
}

static void	handle_movement_release(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player->move_forward = 0;
	else if (keycode == KEY_S)
		player->move_backward = 0;
	else if (keycode == KEY_A)
		player->move_left = 0;
	else if (keycode == KEY_D)
		player->move_right = 0;
}

static void	handle_rotation_release(int keycode, t_player *player)
{
	if (keycode == KEY_LEFT)
		player->rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		player->rotate_right = 0;
}

int	handle_player_keypress(int keycode, t_game *game)
{
	if (!game->window_focused)
		return (0);
	if (keycode == KEY_ESC)
	{
		game->is_running = 0;
		return (1);
	}
	handle_movement_press(keycode, &game->player);
	handle_rotation_press(keycode, &game->player);
	return (0);
}

int	handle_player_keyrelease(int keycode, t_game *game)
{
	if (!game->window_focused)
		return (0);
	handle_movement_release(keycode, &game->player);
	handle_rotation_release(keycode, &game->player);
	return (0);
}
