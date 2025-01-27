/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/27 16:54:35 by jcohen           ###   ########.fr       */
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

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	cos_rot = cos(angle);
	sin_rot = sin(angle);
 	game->player.dir_x = game->player.dir_x * cos_rot - game->player.dir_y
		* sin_rot;
	game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;
	game->player.plane_x = game->player.plane_x * cos_rot - game->player.plane_y
		* sin_rot;
	game->player.plane_y = old_plane_x * sin_rot + game->player.plane_y
		* cos_rot;
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
	if (player->rotate_left)
		rotate_player(game, -ROT_SPEED);
	if (player->rotate_right)
		rotate_player(game, ROT_SPEED);
}
