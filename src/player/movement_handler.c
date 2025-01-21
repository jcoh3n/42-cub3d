/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 01:51:36 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 16:01:19 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	check_collision(t_game *game, double new_x, double new_y)
{
	int		map_x;
	int		map_y;
	double	buffer;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map[map_y][map_x] == '1')
		return (TRUE);
	buffer = 0.1;
	if (game->map[(int)(new_y + buffer)][(int)(new_x + buffer)] == '1'
		|| game->map[(int)(new_y - buffer)][(int)(new_x - buffer)] == '1'
		|| game->map[(int)(new_y + buffer)][(int)(new_x - buffer)] == '1'
		|| game->map[(int)(new_y - buffer)][(int)(new_x + buffer)] == '1')
		return (TRUE);
	return (FALSE);
}

void	update_forward_back(t_game *game, double *new_x, double *new_y)
{
	double	move_distance;

	move_distance = game->move_speed * game->delta_time;
	if (game->player.move_forward)
	{
		*new_x += game->player.dir_x * move_distance;
		*new_y += game->player.dir_y * move_distance;
	}
	if (game->player.move_backward)
	{
		*new_x -= game->player.dir_x * move_distance;
		*new_y -= game->player.dir_y * move_distance;
	}
}

void	update_strafe(t_game *game, double *new_x, double *new_y)
{
	double	move_distance;

	move_distance = game->move_speed * game->delta_time;
	if (game->player.move_left)
	{
		*new_x += game->player.dir_y * move_distance;
		*new_y -= game->player.dir_x * move_distance;
	}
	if (game->player.move_right)
	{
		*new_x -= game->player.dir_y * move_distance;
		*new_y += game->player.dir_x * move_distance;
	}
}

void	update_movement(t_game *game)
{
	double	new_x;
	double	new_y;

	game->delta_time = get_time() - game->last_frame;
	game->last_frame = get_time();
	new_x = game->player.x;
	new_y = game->player.y;
	update_forward_back(game, &new_x, &new_y);
	update_strafe(game, &new_x, &new_y);
	if (!check_collision(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
