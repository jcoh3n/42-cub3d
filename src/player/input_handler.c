/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:54:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/21 01:43:58 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	handle_movement_press(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player->move_forward = 1;
	else if (keycode == KEY_S)
		player->move_backward = 1;
	else if (keycode == KEY_A)
		player->move_left = 1;
	else if (keycode == KEY_D)
		player->move_right = 1;
}

static void	handle_rotation_press(int keycode, t_player *player)
{
	if (keycode == KEY_LEFT)
		player->rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		player->rotate_right = 1;
}

static void	handle_movement_release(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player->move_forward = 0;
	else if (keycode == KEY_S)
		player->move_backward = 0;
	else if (keycode == KEY_A)
		player->move_left = 0;
	else if (keycode == KEY_D)
		player->move_right = 0;
}

static void	handle_rotation_release(int keycode, t_player *player)
{
	if (keycode == KEY_LEFT)
		player->rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		player->rotate_right = 0;
}

int	handle_player_keypress(int keycode, t_game *game)
{
	if (!game->window_focused)
		return (0);
	if (keycode == KEY_ESC)
	{
		game->is_running = 0;
		return (1);
	}
	handle_movement_press(keycode, &game->player);
	handle_rotation_press(keycode, &game->player);
	return (0);
}

static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

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

void	update_movement(t_game *game)
{
	double	current_time;
	double	move_distance;
	double	new_x;
	double	new_y;

	current_time = get_time();
	game->delta_time = current_time - game->last_frame;
	game->last_frame = current_time;
	move_distance = game->move_speed * game->delta_time;
	new_x = game->player.x;
	new_y = game->player.y;
	if (game->player.move_forward)
	{
		new_x += game->player.dir_x * move_distance;
		new_y += game->player.dir_y * move_distance;
	}
	if (game->player.move_backward)
	{
		new_x -= game->player.dir_x * move_distance;
		new_y -= game->player.dir_y * move_distance;
	}
	if (game->player.move_left)
	{
		new_x += game->player.dir_y * move_distance;
		new_y -= game->player.dir_x * move_distance;
	}
	if (game->player.move_right)
	{
		new_x -= game->player.dir_y * move_distance;
		new_y += game->player.dir_x * move_distance;
	}
	if (!check_collision(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
