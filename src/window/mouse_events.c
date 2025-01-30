/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:00:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 16:37:52 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_mouse_capture(t_game *game)
{
	game->state.mouse_captured = !game->state.mouse_captured;
	if (game->state.mouse_captured)
	{
		mlx_mouse_hide(game->renderer.mlx, game->renderer.win);
		mlx_mouse_move(game->renderer.mlx, game->renderer.win,
			get_mouse_center_x(), get_mouse_center_y());
		game->input.last_mouse_x = get_mouse_center_x();
		game->input.last_mouse_y = get_mouse_center_y();
		game->player.rotate_left = 0;
		game->player.rotate_right = 0;
	}
	else
	{
		mlx_mouse_show(game->renderer.mlx, game->renderer.win);
	}
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	double	dx;
	double	rotation_angle;

	(void)y;
	if (!game->state.mouse_captured || !game->state.window_focused)
		return (0);
	dx = x - game->input.last_mouse_x;
	if (fabs(dx) < MOUSE_DEADZONE)
		return (0);
	rotation_angle = dx * MOUSE_SENSITIVITY;
	rotate_player(game, rotation_angle);
	mlx_mouse_move(game->renderer.mlx, game->renderer.win, get_mouse_center_x(),
		get_mouse_center_y());
	game->input.last_mouse_x = get_mouse_center_x();
	game->input.last_mouse_y = get_mouse_center_y();
	return (0);
}
