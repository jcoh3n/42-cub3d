/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/25 16:41:00 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_collision(t_game *game, double new_x, double new_y)
{
	// Add padding for smoother collision
	double padding = 0.1;  // Reduced padding for more precise movement

	// Check map boundaries with padding
	if (new_x - padding < 0 || new_x + padding >= game->map_data->width ||
		new_y - padding < 0 || new_y + padding >= game->map_data->height)
		return (1);

	// Check wall collision with sliding
	int map_x = (int)new_x;
	int map_y = (int)new_y;

	// Check diagonal movement
	if (game->map_data->grid[map_y][map_x] == '1')
	{
		// Try sliding along walls
		if (game->map_data->grid[(int)game->player.y][map_x] != '1')
			return (2);  // Can slide horizontally
		if (game->map_data->grid[map_y][(int)game->player.x] != '1')
			return (3);  // Can slide vertically
		return (1);  // Complete collision
	}

	return (0);  // No collision
}

static void	move_forward_back(t_game *game, double dir)
{
	double	new_x;
	double	new_y;
	double	move_speed;
	int		collision;

	move_speed = game->player.move_speed;
	new_x = game->player.x + dir * game->player.dir_x * move_speed;
	new_y = game->player.y + dir * game->player.dir_y * move_speed;

	collision = check_collision(game, new_x, new_y);
	if (collision == 0)
	{
		// No collision, move normally
		game->player.x = new_x;
		game->player.y = new_y;
	}
	else if (collision == 2)
	{
		// Slide horizontally
		game->player.x = new_x;
	}
	else if (collision == 3)
	{
		// Slide vertically
		game->player.y = new_y;
	}
}

static void	move_left_right(t_game *game, double dir)
{
	double	new_x;
	double	new_y;
	double	move_speed;
	int		collision;

	move_speed = game->player.move_speed;
	new_x = game->player.x + dir * game->player.plane_x * move_speed;
	new_y = game->player.y + dir * game->player.plane_y * move_speed;

	collision = check_collision(game, new_x, new_y);
	if (collision == 0)
	{
		// No collision, move normally
		game->player.x = new_x;
		game->player.y = new_y;
	}
	else if (collision == 2)
	{
		// Slide horizontally
		game->player.x = new_x;
	}
	else if (collision == 3)
	{
		// Slide vertically
		game->player.y = new_y;
	}
}

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	// Smooth rotation
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle) -
		game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) +
		game->player.dir_y * cos(angle);

	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle) -
		game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) +
		game->player.plane_y * cos(angle);
}

void	update_player_position(t_game *game)
{
	// Debug: Print initial position
	printf("Player position before update: x=%f, y=%f, dir_x=%f, dir_y=%f\n",
		game->player.x, game->player.y, game->player.dir_x, game->player.dir_y);

	// Handle forward/backward movement
	if (game->player.move_forward)
	{
		printf("Moving forward\n");
		move_forward_back(game, 1);
	}
	if (game->player.move_backward)
	{
		printf("Moving backward\n");
		move_forward_back(game, -1);
	}

	// Handle left/right strafing
	if (game->player.move_left)
	{
		printf("Moving left\n");
		move_left_right(game, -1);
	}
	if (game->player.move_right)
	{
		printf("Moving right\n");
		move_left_right(game, 1);
	}

	// Handle rotation
	if (game->player.rotate_left)
	{
		printf("Rotating left\n");
		rotate_player(game, -game->player.rot_speed);
	}
	if (game->player.rotate_right)
	{
		printf("Rotating right\n");
		rotate_player(game, game->player.rot_speed);
	}

	// Debug: Print final position
	printf("Player position after update: x=%f, y=%f, dir_x=%f, dir_y=%f\n",
		game->player.x, game->player.y, game->player.dir_x, game->player.dir_y);
} 