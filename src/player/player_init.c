/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/29 16:07:15 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	t_player	*player;
	char		dir;

	player = &game->player;
	dir = game->map_data->player_dir;
	// Initialize position
	player->x = game->map_data->player_x;
	player->y = game->map_data->player_y;
	player->pos_x = player->x;
	player->pos_y = player->y;
	// Initialize direction vectors
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	// Set direction based on starting orientation
	if (dir == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	// Set movement constants
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;
}
