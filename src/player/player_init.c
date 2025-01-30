/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 16:15:03 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_direction(t_player *player, char dir)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	if (dir == 'N')
	{
		player->dir_y = -DIRECTION_VECTOR;
		player->plane_x = PLANE_VECTOR;
	}
	else if (dir == 'S')
	{
		player->dir_y = DIRECTION_VECTOR;
		player->plane_x = -PLANE_VECTOR;
	}
	else if (dir == 'E')
	{
		player->dir_x = DIRECTION_VECTOR;
		player->plane_y = PLANE_VECTOR;
	}
	else if (dir == 'W')
	{
		player->dir_x = -DIRECTION_VECTOR;
		player->plane_y = -PLANE_VECTOR;
	}
}

void	init_player_position(t_player *player, double x, double y)
{
	player->x = x;
	player->y = y;
	player->pos_x = x;
	player->pos_y = y;
}

void	init_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	init_player_position(player, game->map_data->player_x,
		game->map_data->player_y);
	init_player_direction(player, game->map_data->player_dir);
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;
}
