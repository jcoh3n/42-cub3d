/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:53:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 16:17:43 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_collision(t_game *game, double x, double y)
{
	if (game->map_data->grid[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	update_forward(t_game *game, t_player *p)
{
	double	new_x;
	double	new_y;

	new_x = p->pos_x + p->dir_x * MOVE_SPEED;
	new_y = p->pos_y + p->dir_y * MOVE_SPEED;
	if (!check_collision(game, new_x, p->pos_y))
		p->pos_x = new_x;
	if (!check_collision(game, p->pos_x, new_y))
		p->pos_y = new_y;
}

void	update_backward(t_game *game, t_player *p)
{
	double	new_x;
	double	new_y;

	new_x = p->pos_x - p->dir_x * MOVE_SPEED;
	new_y = p->pos_y - p->dir_y * MOVE_SPEED;
	if (!check_collision(game, new_x, p->pos_y))
		p->pos_x = new_x;
	if (!check_collision(game, p->pos_x, new_y))
		p->pos_y = new_y;
}

void	update_strafe_movement(t_game *game, t_player *p)
{
	double	new_x;
	double	new_y;

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

void	update_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (p->move_forward)
		update_forward(game, p);
	if (p->move_backward)
		update_backward(game, p);
	update_strafe_movement(game, p);
	rotate_player(game);
}
