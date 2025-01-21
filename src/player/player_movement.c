/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:53:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 16:32:02 by jcohen           ###   ########.fr       */
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
	if (game->map_data->grid[map_y][map_x] == '1')
		return (TRUE);
	buffer = 0.2;
	if (game->map_data->grid[(int)(new_y + buffer)][(int)(new_x + buffer)] == '1'
		|| game->map_data->grid[(int)(new_y - buffer)][(int)(new_x - buffer)] == '1'
		|| game->map_data->grid[(int)(new_y + buffer)][(int)(new_x - buffer)] == '1'
		|| game->map_data->grid[(int)(new_y - buffer)][(int)(new_x + buffer)] == '1')
		return (TRUE);
	return (FALSE);
}

static void	try_movement(t_game *game, double new_x, double new_y, t_player *p)
{
	if (!check_collision(game, new_x, p->pos_y))
		p->pos_x = new_x;
	if (!check_collision(game, p->pos_x, new_y))
		p->pos_y = new_y;
}

static void	apply_movement(t_game *game, t_player *p, double dir_x, double dir_y)
{
	double	move_distance;
	double	new_x;
	double	new_y;

	move_distance = MOVE_SPEED * game->delta_time;
	new_x = p->pos_x + dir_x * move_distance;
	new_y = p->pos_y + dir_y * move_distance;
	try_movement(game, new_x, new_y, p);
}

void	update_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (p->move_forward)
		apply_movement(game, p, p->dir_x, p->dir_y);
	if (p->move_backward)
		apply_movement(game, p, -p->dir_x, -p->dir_y);
	if (p->move_left)
		apply_movement(game, p, -p->dir_y, p->dir_x);
	if (p->move_right)
		apply_movement(game, p, p->dir_y, -p->dir_x);
	rotate_player(game);
}
