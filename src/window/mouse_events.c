/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:00:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/29 15:45:23 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_mouse_capture(t_game *game)
{
	game->state.mouse_captured = !game->state.mouse_captured;
	if (game->state.mouse_captured)
	{
		mlx_mouse_hide(game->renderer.mlx, game->renderer.win);
		mlx_mouse_move(game->renderer.mlx, game->renderer.win, MOUSE_CENTER_X, MOUSE_CENTER_Y);
		game->input.last_mouse_x = MOUSE_CENTER_X;
		game->input.last_mouse_y = MOUSE_CENTER_Y;
		// Disable keyboard rotation when mouse is captured
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

	(void)y;  // Unused parameter
	if (!game->state.mouse_captured || !game->state.window_focused)
		return (0);

	dx = x - game->input.last_mouse_x;
	
	// Ignore very small movements (deadzone)
	if (fabs(dx) < MOUSE_DEADZONE)
		return (0);

	rotation_angle = dx * MOUSE_SENSITIVITY;

	// Fix rotation direction (positive dx = rotate right)
	rotate_player(game, rotation_angle);
		
	// Always recenter the mouse to prevent jerky movement
	mlx_mouse_move(game->renderer.mlx, game->renderer.win, MOUSE_CENTER_X, MOUSE_CENTER_Y);
	game->input.last_mouse_x = MOUSE_CENTER_X;
	game->input.last_mouse_y = MOUSE_CENTER_Y;

	return (0);
} 