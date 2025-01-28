/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:00:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/28 20:46:00 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_mouse_capture(t_game *game)
{
	game->mouse_captured = !game->mouse_captured;
	if (game->mouse_captured)
	{
		mlx_mouse_hide(game->mlx, game->win);
		mlx_mouse_move(game->mlx, game->win, MOUSE_CENTER_X, MOUSE_CENTER_Y);
		game->last_mouse_x = MOUSE_CENTER_X;
		game->last_mouse_y = MOUSE_CENTER_Y;
		// Disable keyboard rotation when mouse is captured
		game->player.rotate_left = 0;
		game->player.rotate_right = 0;
	}
	else
	{
		mlx_mouse_show(game->mlx, game->win);
	}
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	double	dx;
	double	rotation_angle;

	(void)y;  // Unused parameter
	if (!game->mouse_captured || !game->window_focused)
		return (0);

	dx = x - game->last_mouse_x;
	
	// Ignore very small movements (deadzone)
	if (fabs(dx) < MOUSE_DEADZONE)
		return (0);

	rotation_angle = dx * MOUSE_SENSITIVITY;

	// Fix rotation direction (positive dx = rotate right)
	rotate_player(game, rotation_angle);
		
	// Always recenter the mouse to prevent jerky movement
	mlx_mouse_move(game->mlx, game->win, MOUSE_CENTER_X, MOUSE_CENTER_Y);
	game->last_mouse_x = MOUSE_CENTER_X;
	game->last_mouse_y = MOUSE_CENTER_Y;

	return (0);
} 