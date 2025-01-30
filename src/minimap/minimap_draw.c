/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:52:17 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:53:35 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square_helper(t_game *game, t_square_data *data)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;

	y = 0;
	while (y < data->scale)
	{
		x = 0;
		while (x < data->scale)
		{
			screen_x = data->map_x * data->scale + x - data->offset_x;
			screen_y = data->map_y * data->scale + y - data->offset_y;
			put_pixel_minimap(game, screen_x, screen_y, data->color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *game, int map_x, int map_y, int color)
{
	t_square_data	data;

	data.scale = game->renderer.minimap.scale;
	data.offset_x = (int)(game->player.x * data.scale) - MINIMAP_RADIUS;
	data.offset_y = (int)(game->player.y * data.scale) - MINIMAP_RADIUS;
	data.map_x = map_x;
	data.map_y = map_y;
	data.color = color;
	draw_square_helper(game, &data);
}

static void	init_arrow_coords(t_draw_player_data *data)
{
	data->angle = atan2(data->player->dir_y, data->player->dir_x);
	data->arrow_x[0] = MINIMAP_RADIUS + (int)(data->size * 1.1
			* cos(data->angle));
	data->arrow_y[0] = MINIMAP_RADIUS + (int)(data->size * 1.1
			* sin(data->angle));
	data->arrow_x[1] = MINIMAP_RADIUS + (int)(data->size * 0.7 * cos(data->angle
				+ M_PI * 0.72));
	data->arrow_y[1] = MINIMAP_RADIUS + (int)(data->size * 0.7 * sin(data->angle
				+ M_PI * 0.72));
	data->arrow_x[2] = MINIMAP_RADIUS + (int)(data->size * 0.7 * cos(data->angle
				- M_PI * 0.72));
	data->arrow_y[2] = MINIMAP_RADIUS + (int)(data->size * 0.7 * sin(data->angle
				- M_PI * 0.72));
}

void	draw_player(t_game *game)
{
	t_draw_player_data	data;

	data.size = game->renderer.minimap.scale * 1.5;
	if (data.size < 12)
		data.size = 12;
	data.player = &game->player;
	init_arrow_coords(&data);
	draw_player_triangle(game, &data);
}
