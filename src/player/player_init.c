/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:52:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 01:40:25 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_direction_vectors(t_player *player, char direction)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	if (direction == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (direction == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player->pos_x = game->map->player_x + 0.5;
	player->pos_y = game->map->player_y + 0.5;
	init_direction_vectors(player, game->map->player_dir);
	player->move_forward = 0;
	player->move_backward = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
}

int	handle_player_keyrelease(int keycode, t_game *game)
{
	if (!game->window_focused)
		return (0);
	handle_movement_release(keycode, &game->player);
	handle_rotation_release(keycode, &game->player);
	return (0);
}
