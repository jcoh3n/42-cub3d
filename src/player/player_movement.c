/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/25 18:04:39 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_collision(t_game *game, double new_x, double new_y)
{
	double	padding;
	int		map_x;
	int		map_y;

	padding = 0.1;
	if (new_x - padding < 0 || new_x + padding >= game->map_data->width || new_y
		- padding < 0 || new_y + padding >= game->map_data->height)
		return (1);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map_data->grid[map_y][map_x] == '1')
	{
		if (game->map_data->grid[(int)game->player.y][map_x] != '1')
			return (2);
		if (game->map_data->grid[map_y][(int)game->player.x] != '1')
			return (3);
		return (1);
	}
	return (0);
}

static void	handle_rotation(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	if (player->rotate_left || player->rotation_direction < 0)
	{
		rot_speed = (player->rotation_direction < 0) ? MOUSE_SENSITIVITY : ROT_SPEED;
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
		player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
	}
	if (player->rotate_right || player->rotation_direction > 0)
	{
		rot_speed = (player->rotation_direction > 0) ? MOUSE_SENSITIVITY : ROT_SPEED;
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
		player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
	}
}

void	update_player_position(t_game *game)
{
	t_player	*player;
	double		new_x;
	double		new_y;
	int			collision;

	player = &game->player;
	if (player->move_forward)
	{
		new_x = player->x + player->dir_x * MOVE_SPEED;
		new_y = player->y + player->dir_y * MOVE_SPEED;
		collision = check_collision(game, new_x, new_y);
		if (collision == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		else if (collision == 2)
			player->x = new_x;
		else if (collision == 3)
			player->y = new_y;
	}
	if (player->move_backward)
	{
		new_x = player->x - player->dir_x * MOVE_SPEED;
		new_y = player->y - player->dir_y * MOVE_SPEED;
		collision = check_collision(game, new_x, new_y);
		if (collision == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		else if (collision == 2)
			player->x = new_x;
		else if (collision == 3)
			player->y = new_y;
	}
	if (player->move_left)
	{
		new_x = player->x - player->plane_x * MOVE_SPEED;
		new_y = player->y - player->plane_y * MOVE_SPEED;
		collision = check_collision(game, new_x, new_y);
		if (collision == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		else if (collision == 2)
			player->x = new_x;
		else if (collision == 3)
			player->y = new_y;
	}
	if (player->move_right)
	{
		new_x = player->x + player->plane_x * MOVE_SPEED;
		new_y = player->y + player->plane_y * MOVE_SPEED;
		collision = check_collision(game, new_x, new_y);
		if (collision == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		else if (collision == 2)
			player->x = new_x;
		else if (collision == 3)
			player->y = new_y;
	}
	handle_rotation(player);
}
