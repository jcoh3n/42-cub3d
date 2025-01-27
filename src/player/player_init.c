/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/27 17:27:06 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player(t_game *game)
{
	t_player	*player;
	char		dir;

	player = &game->player;
	dir = game->map_data->player_dir;
	player->x = game->map_data->player_x;
	player->y = game->map_data->player_y;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
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
	player->move_forward = 0;
	player->move_backward = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->rotation_direction = 0;
}
