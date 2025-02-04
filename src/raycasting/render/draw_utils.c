/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wander <wander@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:12:36 by wander            #+#    #+#             */
/*   Updated: 2025/02/04 20:12:37 by wander           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *game, int x, t_wall_render *wall,
		t_color_data *colors)
{
	int	y;

	colors->ceiling_color = (game->map_data->ceiling.r << 16) | (game->map_data->ceiling.g << 8) | game->map_data->ceiling.b;
	y = 0;
	while (y < wall->wall_top)
	{
		put_pixel(&game->renderer.frame, x, y, colors->ceiling_color);
		y++;
	}
}

void	draw_textured_wall(t_game *game, int x, t_wall_render *wall,
		t_texture *texture, t_color_data *colors)
{
	int		y;
	char	*pixel_addr;

	y = wall->wall_top;
	while (y < wall->wall_bottom)
	{
		wall->tex_y = (int)wall->tex_pos & (texture->height - 1);
		pixel_addr = texture->addr + (wall->tex_y * texture->line_length
				+ wall->tex_x * (texture->bits_per_pixel / 8));
		if (texture->endian == 1)
			colors->color = ((unsigned char)pixel_addr[0] << 24 | (unsigned char)pixel_addr[1] << 16 | (unsigned char)pixel_addr[2] << 8 | (unsigned char)pixel_addr[3]);
		else
			colors->color = *(unsigned int *)pixel_addr;
		colors->r = ((colors->color >> 16) & 0xFF) * wall->shade;
		colors->g = ((colors->color >> 8) & 0xFF) * wall->shade;
		colors->b = (colors->color & 0xFF) * wall->shade;
		colors->color = (colors->r << 16) | (colors->g << 8) | colors->b;
		put_pixel(&game->renderer.frame, x, y, colors->color);
		wall->tex_pos += wall->step;
		y++;
	}
}

void	draw_floor(t_game *game, int x, t_wall_render *wall,
		t_color_data *colors)
{
	int	y;

	colors->floor_color = (game->map_data->floor.r << 16) | (game->map_data->floor.g << 8) | game->map_data->floor.b;
	y = wall->wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(&game->renderer.frame, x, y, colors->floor_color);
		y++;
	}
}
