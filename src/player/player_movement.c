/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:53:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 01:53:59 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_collision(t_game *game, double x, double y)
{
	if (game->map->grid[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

static void	move_forward_backward(t_game *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &game->player;
	if (p->move_forward)
	{
		new_x = p->pos_x + p->dir_x * MOVE_SPEED;
		new_y = p->pos_y + p->dir_y * MOVE_SPEED;
		if (!check_collision(game, new_x, p->pos_y))
			p->pos_x = new_x;
		if (!check_collision(game, p->pos_x, new_y))
			p->pos_y = new_y;
	}
	if (p->move_backward)
	{
		new_x = p->pos_x - p->dir_x * MOVE_SPEED;
		new_y = p->pos_y - p->dir_y * MOVE_SPEED;
		if (!check_collision(game, new_x, p->pos_y))
			p->pos_x = new_x;
		if (!check_collision(game, p->pos_x, new_y))
			p->pos_y = new_y;
	}
}

static void	move_left_right(t_game *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &game->player;
	if (p->move_left)
	{
		new_x = p->pos_x - p->dir_y * MOVE_SPEED;
		new_y = p->pos_y + p->dir_x * MOVE_SPEED;
		if (!check_collision(game, new_x, p->pos_y))
			p->pos_x = new_x;
		if (!check_collision(game, p->pos_x, new_y))
			p->pos_y = new_y;
	}
	if (p->move_right)
	{
		new_x = p->pos_x + p->dir_y * MOVE_SPEED;
		new_y = p->pos_y - p->dir_x * MOVE_SPEED;
		if (!check_collision(game, new_x, p->pos_y))
			p->pos_x = new_x;
		if (!check_collision(game, p->pos_x, new_y))
			p->pos_y = new_y;
	}
}

static void	rotate_player(t_game *game)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &game->player;
	if (p->rotate_left)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
	if (p->rotate_right)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y
			* sin(-ROT_SPEED);
		p->plane_y = old_plane_x * sin(-ROT_SPEED) + p->plane_y
			* cos(-ROT_SPEED);
	}
}

void	update_player(t_game *game)
{
	move_forward_backward(game);
	move_left_right(game);
	rotate_player(game);
}
