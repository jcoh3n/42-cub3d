/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:10:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/25 16:22:57 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_player_direction(t_player *player, char dir)
{
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
}

void	init_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player->x = game->map_data->player_x + 0.5;
	player->y = game->map_data->player_y + 0.5;

	// Set movement speeds
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;

	// Initialize movement flags
	player->move_forward = 0;
	player->move_backward = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;

	// Set initial direction based on map
	set_player_direction(player, game->map_data->player_dir);

	// Debug: Print initial player state
	printf("\nPlayer initialized:\n");
	printf("Position: x=%f, y=%f\n", player->x, player->y);
	printf("Direction: dir_x=%f, dir_y=%f\n", player->dir_x, player->dir_y);
	printf("Plane: plane_x=%f, plane_y=%f\n", player->plane_x, player->plane_y);
	printf("Speeds: move=%f, rot=%f\n", player->move_speed, player->rot_speed);
	printf("Initial map direction: %c\n\n", game->map_data->player_dir);
} 