/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 19:21:38 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_collision_axis(t_game *game, double new_x, double new_y,
		int check_x)
{
	double	padding;
	int		map_x;
	int		map_y;

	padding = 0.17;
	if (check_x)
	{
		if (new_x - padding < 0 || new_x + padding >= game->map_data->width)
			return (1);
		map_x = (int)new_x;
		map_y = (int)game->player.y;
	}
	else
	{
		if (new_y - padding < 0 || new_y + padding >= game->map_data->height)
			return (1);
		map_x = (int)game->player.x;
		map_y = (int)new_y;
	}
	if (game->map_data->grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
		* cos(angle);
}

static void	handle_movement(t_game *game, double dir_x, double dir_y)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &game->player;
	new_x = player->x + dir_x * player->move_speed;
	new_y = player->y + dir_y * player->move_speed;
	if (!check_collision_axis(game, new_x, player->y, 1))
		player->x = new_x;
	if (!check_collision_axis(game, player->x, new_y, 0))
		player->y = new_y;
	player->pos_x = player->x;
	player->pos_y = player->y;
}

void	update_player_position(t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (game->input.move_forward)
		handle_movement(game, player->dir_x, player->dir_y);
	if (game->input.move_backward)
		handle_movement(game, -player->dir_x, -player->dir_y);
	if (game->input.move_left)
		handle_movement(game, -player->plane_x, -player->plane_y);
	if (game->input.move_right)
		handle_movement(game, player->plane_x, player->plane_y);
	if (game->input.rotate_left)
		rotate_player(game, -player->rot_speed);
	if (game->input.rotate_right)
		rotate_player(game, player->rot_speed);
}
